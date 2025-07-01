import './PlantInfo.css';

import { useEffect, useState } from 'react';   

function PlantInfo({ averageMoisture }) {
    const [lastWatered, setLastWatered] = useState(null);

    useEffect(() => {
    fetch("https://quenchtessential-backend.onrender.com/last-watered")
        .then((res) => res.json())
        .then((data) => {
        if (data.lastWatered) {
            const date = new Date(data.lastWatered + ' UTC');

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
        <h3 className="plant-name">Plant Info</h3>
        <img 
            src="bok_choy_wide.jpg" 
            alt="Plant" 
            className="plant-image"
        />
        <p className="plant-species">LeBloom (Peace Lily)</p>
        {averageMoisture !== null && (
            <p className="plant-stat" align="left"><strong>Avg Moisture (Last 24 h)</strong>: {averageMoisture}</p>
        )}

        {lastWatered && (
            <p className="plant-stat" align="left"><strong>Last Watered</strong>: {lastWatered}</p>
        )}
        </div>
    );
}

export default PlantInfo;
