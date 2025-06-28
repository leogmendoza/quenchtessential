import './Dashboard.css';
import { useState, useEffect } from 'react';

import {
  Chart as ChartJS,
  TimeScale,
  LinearScale,
  PointElement,
  LineElement,
  Tooltip,
  Legend
} from 'chart.js';
import { Line } from 'react-chartjs-2';
import 'chartjs-adapter-date-fns';

ChartJS.register(TimeScale, LinearScale, PointElement, LineElement, Tooltip, Legend);

function Dashboard() {
    const [readings, setReadings] = useState([]);

    useEffect( () => {
        // Fetch moisture readings from backend
        const fetchData = async () => {
            try {
            const res = await fetch('http://localhost:3000/history');
            const json = await res.json();

            // Order by oldest to newest
            setReadings( json.reverse() ); 
            } catch (err) {
                console.error('Failed to fetch data:', err);
            }
        };

        // Fetch upon startup
        fetchData(); 

        // Poll for a reading every 10 seconds
        const interval = setInterval(fetchData, 10000);

        return () => clearInterval(interval); // cleanup on unmount
    }, [] );

    // Define the chart's input
    const chartData = {
        labels: readings.map(r => r.timestamp),
        datasets: [ {
            label: 'Soil Moisture',
            data: readings.map(r => r.moisture),
            borderColor: 'green',
            fill: false,

            borderColor: '#8b5e3c',             // Line:            Chocolate           
            pointBackgroundColor: '#8b5e3c',    // Point Fill:      Chocolate     
            pointBorderColor: '#5d4037'         // Point Outline:   Espresso
        } ]
    };

    // Configure the chart's formatting
    const chartOptions = {
        responsive: true,
        plugins: {
            legend: {
                position: 'top',
                align: 'center',
                labels: {
                    color: '#ffffff',
                    usePointStyle: true,
                    boxWidth: 10
                }
                },
                tooltip: {
                    titleColor: '#ffffff',
                    bodyColor: '#ffffff',
                    backgroundColor: '#1b5e20'
            }
        },
        scales: {
            x: {
                type: 'time',
                time: {
                    tooltipFormat: 'MMM dd, HH:mm'
                },
                ticks: {
                    color: '#ffffff',
                    font: {
                        size: 12,
                        weight: '500'
                    }
                },
                title: {
                    display: true,
                    text: 'Timestamp',
                    color: '#ffffff',
                    font: {
                        size: 14,
                        weight: '700'
                    },
                    align: 'center'
                },
                grid: {
                    color: 'rgba(255, 255, 255, 0.2)',
                    lineWidth: 1.5
                }

            },
            y: {
                beginAtZero: true,
                ticks: {
                    color: '#ffffff',
                    font: {
                        size: 12,
                        weight: '500'
                    }
                },
                title: {
                    display: true,
                    text: 'Moisture Level',
                    color: '#ffffff',
                    font: {
                        size: 14,
                        weight: '700'
                    },
                    align: 'center'
                },
                grid: {
                    color: 'rgba(255, 255, 255, 0.2)',
                    lineWidth: 1.5
                }
            }
        }
    };


    return (
        <div className="dashboard-container">
            <h2 className="dashboard-title">🌱 Quenchtessential Dashboard</h2>
            <Line data={chartData} options={chartOptions} />
        </div>
    );
};

export default Dashboard;