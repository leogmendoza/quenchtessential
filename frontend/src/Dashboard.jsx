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
            fill: false
        } ]
    };

    // Configure the chart's formatting
    const chartOptions = {
        responsive: true,
        scales: {
            x: {
            type: 'time',
            time: {
                tooltipFormat: 'MMM dd, HH:mm'
            },
            title: {
                display: true,
                text: 'Timestamp'
            }
            },
            y: {
            beginAtZero: true,
            title: {
                display: true,
                text: 'Moisture Level'
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