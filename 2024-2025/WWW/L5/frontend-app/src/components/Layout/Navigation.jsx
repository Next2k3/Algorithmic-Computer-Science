import React, { useState } from 'react';
import { Link, useLocation } from 'react-router-dom';
import { useAuth } from '../../context/AuthContext'; // Importuj AuthContext

const Navigation = () => {
  const [isMenuOpen, setIsMenuOpen] = useState(false);
  const location = useLocation();
  
  // Użyj AuthContext zamiast bezpośredniego dostępu do localStorage
  const { user, logout, isAuthenticated } = useAuth();

  const handleLogout = () => {
    logout(); // Użyj funkcji logout z AuthContext
  };

  const isActive = (path) => {
    return location.pathname === path || location.pathname.startsWith(path + '/');
  };

  // Nawigacja dla zalogowanych użytkowników
  const navItems = [
    { path: '/dashboard', label: 'Dashboard', icon: '📊' },
    { path: '/projects', label: 'Projekty', icon: '📁' },
    { path: '/profile', label: 'Profil', icon: '👤' },
  ];

  // Dodaj panel admina jeśli użytkownik to admin
  if (user?.role === 'admin') {
    navItems.push({ path: '/users', label: 'Użytkownicy', icon: '👥' });
  }

  // Jeśli użytkownik nie jest zalogowany, pokaż podstawową nawigację
  if (!isAuthenticated) {
    return (
      <nav className="nav-container">
        <div className="container">
          <div className="nav-content">
            <Link to="/" className="nav-logo">
              📋 Projekty
            </Link>
            <div className="nav-auth-links">
              <Link to="/login" className="nav-link">
                Logowanie
              </Link>
              <Link to="/register" className="nav-link nav-link-primary">
                Rejestracja
              </Link>
            </div>
          </div>
        </div>
      </nav>
    );
  }

  return (
    <nav className="nav-container">
      <div className="container">
        <div className="nav-content">
          {/* Logo */}
          <Link to="/dashboard" className="nav-logo">
            📋 Projekty
          </Link>

          {/* Desktop Menu */}
          <div className="nav-menu desktop">
            {navItems.map(item => (
              <Link
                key={item.path}
                to={item.path}
                className={`nav-link ${isActive(item.path) ? 'active' : ''}`}
              >
                <span className="nav-icon">{item.icon}</span>
                {item.label}
              </Link>
            ))}
          </div>

          {/* User Menu Desktop */}
          <div className="nav-user-menu desktop">
            <div className="nav-user-info">
              <span className="user-greeting">Witaj, </span>
              <span className="user-name">{user.name}</span>
              {user.role === 'admin' && (
                <span className="user-role">Admin</span>
              )}
            </div>
            <button
              onClick={handleLogout}
              className="nav-logout-btn"
              title="Wyloguj się"
            >
              🚪 Wyloguj
            </button>
          </div>

          {/* Mobile Menu Button */}
          <button
            onClick={() => setIsMenuOpen(!isMenuOpen)}
            className="nav-mobile-toggle"
            aria-label="Toggle menu"
          >
            <svg className="nav-mobile-icon" fill="none" viewBox="0 0 24 24" stroke="currentColor">
              {isMenuOpen ? (
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M6 18L18 6M6 6l12 12" />
              ) : (
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M4 6h16M4 12h16M4 18h16" />
              )}
            </svg>
          </button>
        </div>

        {/* Mobile Menu */}
        {isMenuOpen && (
          <div className="nav-mobile-menu">
            <div className="nav-mobile-links">
              {navItems.map(item => (
                <Link
                  key={item.path}
                  to={item.path}
                  onClick={() => setIsMenuOpen(false)}
                  className={`nav-mobile-link ${isActive(item.path) ? 'active' : ''}`}
                >
                  <span className="nav-icon">{item.icon}</span>
                  {item.label}
                </Link>
              ))}
            </div>
            
            <div className="nav-mobile-user">
              <div className="nav-mobile-user-info">
                <div className="user-name">{user.name}</div>
                <div className="user-email">{user.email}</div>
                {user.role === 'admin' && (
                  <div className="user-role">Administrator</div>
                )}
              </div>
              <button
                onClick={handleLogout}
                className="nav-mobile-logout"
              >
                🚪 Wyloguj się
              </button>
            </div>
          </div>
        )}
      </div>
    </nav>
  );
};

export default Navigation;
