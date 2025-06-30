import Header from './Header';
import PlantInfo from './PlantInfo';
import Dashboard from './Dashboard';

function App() {
  return (
    <>
      <Header />
        <main className="app-main">
          <Dashboard renderInfo={(avgMoisture) => <PlantInfo averageMoisture={avgMoisture} />}/>
        </main>
    </>
  );
}

export default App;