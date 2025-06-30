import './PlantInfo.css';

import { useEffect, useState } from 'react';   

function PlantInfo({ averageMoisture }) {
    const [lastWatered, setLastWatered] = useState(null);

    useEffect(() => {
    fetch("http://localhost:3000/last-watered")
        .then((res) => res.json())
        .then((data) => {
        if (data.lastWatered) {
            const date = new Date(data.lastWatered);
            setLastWatered(date.toLocaleString('en-US', {
            timeZone: 'America/Toronto',
            hour: 'numeric',
            minute: '2-digit',
            hour12: true,
            weekday: 'short',
            month: 'short',
            day: 'numeric'
            }));
        }
        })
        .catch((err) => {
        console.error("Failed to fetch last watered time:", err);
        });
    }, []);

    return (
        <div className="plant-info-card">
        <h3 className="plant-name">Plant Name</h3>
        <p className="plant-species">Plant Species</p>
        <img 
            src="bok_choy_wide.jpg" 
            alt="Plant" 
            className="plant-image"
        />
        {averageMoisture !== null && (
            <p className="plant-stat">Avg Moisture (Last 24 h): {averageMoisture}</p>
        )}

        {lastWatered && (
            <p className="plant-stat">Last Watered: {lastWatered}</p>
        )}
        </div>
    );
}

export default PlantInfo;
