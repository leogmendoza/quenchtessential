import './PlantInfo.css';

function PlantInfo({ averageMoisture }) {
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
    </div>
  );
}

export default PlantInfo;
