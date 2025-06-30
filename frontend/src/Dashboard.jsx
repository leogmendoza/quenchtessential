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
    const [error, setError] = useState(null);
    const [hasLoadedOnce, setHasLoadedOnce] = useState(false);
    const [range, setRange] = useState("24h");

    useEffect( () => {
        // Fetch moisture readings from backend
        const fetchData = async () => {
            try {
                const res = await fetch(`https://quenchtessential-backend.onrender.com/history?range=${range}`);
                if (!res.ok) throw new Error("Network error");

                const json = await res.json();

                // Order by oldest to newest
                setReadings( json.reverse() ); 

                if (json.length > 0) setHasLoadedOnce(true);
                
                setError(null);
            } catch (err) {
                console.error('Failed to fetch data:', err);
            } 
        };

        // Fetch upon startup
        fetchData(); 

        // Poll for a reading every 10 seconds
        const interval = setInterval(fetchData, 10000);

        return () => clearInterval(interval); // cleanup on unmount
    }, [range] );

    // Define the chart's input
    const chartData = {
        datasets: [ {
            label: 'Soil Moisture',
            data: readings.map(r => ({
                x: new Date(r.timestamp + ' UTC'),
                y: r.moisture
            })),
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
                    boxWidth: 10,
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
                    tooltipFormat: 'MMM dd, HH:mm',
                },
                ticks: {
                    callback: function(value) {
                        const utcDate = new Date(value);

                        return utcDate.toLocaleString('en-US', {
                            timeZone: 'America/Toronto',
                            hour: '2-digit',
                            minute: '2-digit',
                            hour12: true
                        });
                    },
                    color: '#ffffff',
                    font: {
                        size: 12,
                        weight: '500'
                    }
                },
                title: {
                    display: true,
                    text: 'Time',
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
                    text: 'Moisture',
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
            <h2 className="dashboard-title">Dashboard</h2>

            {error && !hasLoadedOnce ? (
                <p style={{ color: 'white' }}>{error}</p>
            ) : !hasLoadedOnce ? (
                <p style={{ color: 'white' }}>Sorry . . . loading moisture data 0_o</p>
            ) : readings.length === 0 ? (
                <p style={{ color: 'white' }}>No readings yet.</p>
            ) : (
                <Line data={chartData} options={chartOptions} />
            )}

            <div className="range-selector">
                <label htmlFor="range-select">View Range:</label>
                <select
                    id="range-select"
                    value={range}
                    onChange={(e) => setRange(e.target.value)}
                >
                    <option value="24h">Last 24 hours</option>
                    <option value="7d">Last 7 days</option>
                    <option value="all">All data</option>
                </select>
            </div>
        </div>
    );
};

export default Dashboard;