import './Header.css';

function Header() {
  return (
    <header className="dashboard-banner">
        <h1 className="banner-title">🌱 Quenchtessential</h1>
        <nav>
        <a
        href="https://github.com/leogmendoza/quenchtessential" 
        className="repo-link"
        target="_blank"
        rel="noopener noreferrer"
        >
        <img
            src="https://upload.wikimedia.org/wikipedia/commons/9/91/Octicons-mark-github.svg"
            alt="GitHub"
            className="github-icon"
        /> Repo
        </a>
        </nav>
    </header>
  );
}

export default Header;
