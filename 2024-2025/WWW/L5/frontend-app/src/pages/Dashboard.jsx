import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';

const Dashboard = () => {
  const [stats, setStats] = useState({
    totalProjects: 0,
    activeProjects: 0,
    completedProjects: 0,
    onHoldProjects: 0
  });
  const [recentProjects, setRecentProjects] = useState([]);
  const [recentComments, setRecentComments] = useState([]);
  const [loading, setLoading] = useState(true);
  const [user, setUser] = useState(null);

  useEffect(() => {
    const userData = localStorage.getItem('user');
    if (userData) {
      setUser(JSON.parse(userData));
    }
    fetchDashboardData();
  }, []);

  const fetchDashboardData = async () => {
    try {
      const token = localStorage.getItem('token');
      
      // Pobierz projekty użytkownika
      const projectsResponse = await fetch('/api/projects?limit=5&sortBy=createdAt', {
        headers: {
          'Authorization': `Bearer ${token}`
        }
      });
      const projectsData = await projectsResponse.json();
      
      if (projectsData.results) {
        // Filtruj tylko projekty z prawidłowymi danymi owner
        const validProjects = projectsData.results.filter(p => 
          p && p.owner && p.owner._id
        );
        
        setRecentProjects(validProjects);
        
        // Oblicz statystyki - dodaj sprawdzenie czy user istnieje
        const currentUser = JSON.parse(localStorage.getItem('user') || '{}');
        if (currentUser.id) {
          const userProjects = validProjects.filter(p => 
            p.owner && p.owner._id === currentUser.id
          );
          
          setStats({
            totalProjects: userProjects.length,
            activeProjects: userProjects.filter(p => p.status === 'active').length,
            completedProjects: userProjects.filter(p => p.status === 'completed').length,
            onHoldProjects: userProjects.filter(p => p.status === 'on-hold').length
          });
        }
      }
      
    } catch (error) {
      console.error('Error fetching dashboard data:', error);
    } finally {
      setLoading(false);
    }
  };

  const getStatusBadge = (status) => {
    const statusClasses = {
      'active': 'status-badge status-active',
      'completed': 'status-badge status-completed',
      'on-hold': 'status-badge status-on-hold'
    };
    
    const statusLabels = {
      'active': 'Aktywny',
      'completed': 'Zakończony',
      'on-hold': 'Wstrzymany'
    };
    
    return (
      <span className={statusClasses[status]}>
        {statusLabels[status]}
      </span>
    );
  };

  const formatDate = (dateString) => {
    return new Date(dateString).toLocaleDateString('pl-PL', {
      day: '2-digit',
      month: '2-digit',
      year: 'numeric'
    });
  };

  if (loading) {
    return (
      <div className="loading">
        <div className="loading-spinner">⏳</div>
        <p>Ładowanie danych...</p>
      </div>
    );
  }

  return (
    <div className="dashboard">
      <div className="dashboard-header">
        <h1 className="page-title">
          👋 Witaj, {user?.name || 'Użytkowniku'}!
        </h1>
        <p className="dashboard-subtitle">
          Oto przegląd Twojih projektów i aktywności
        </p>
      </div>

      {/* Statystyki */}
      <div className="stats-grid">
        <div className="stat-card">
          <div className="stat-icon">📊</div>
          <div className="stat-content">
            <div className="stat-number">{stats.totalProjects}</div>
            <div className="stat-label">Wszystkie projekty</div>
          </div>
        </div>
        
        <div className="stat-card">
          <div className="stat-icon">🚀</div>
          <div className="stat-content">
            <div className="stat-number">{stats.activeProjects}</div>
            <div className="stat-label">Aktywne</div>
          </div>
        </div>
        
        <div className="stat-card">
          <div className="stat-icon">✅</div>
          <div className="stat-content">
            <div className="stat-number">{stats.completedProjects}</div>
            <div className="stat-label">Zakończone</div>
          </div>
        </div>
        
        <div className="stat-card">
          <div className="stat-icon">⏸️</div>
          <div className="stat-content">
            <div className="stat-number">{stats.onHoldProjects}</div>
            <div className="stat-label">Wstrzymane</div>
          </div>
        </div>
      </div>

      <div className="dashboard-content">
        {/* Ostatnie projekty */}
        <div className="dashboard-section">
          <div className="section-header">
            <h2 className="section-title">📁 Ostatnie projekty</h2>
            <Link to="/projects" className="section-link">
              Zobacz wszystkie →
            </Link>
          </div>
          
          <div className="section-content">
            {recentProjects.length > 0 ? (
              <div className="projects-list">
                {recentProjects.slice(0, 5).map(project => (
                  <div key={project._id} className="project-item">
                    <div className="project-main">
                      <h3 className="project-title">
                        <Link to={`/projects/${project._id}`}>
                          {project.name}
                        </Link>
                      </h3>
                      <p className="project-description">
                        {project.description || 'Brak opisu'}
                      </p>
                    </div>
                    <div className="project-meta">
                      <div className="project-details">
                        <span className="project-category">
                          🏷️ {project.category}
                        </span>
                        <span className="project-owner">
                          👤 {project.owner?.name || 'Nieznany użytkownik'}
                        </span>
                        <span className="project-date">
                          📅 {formatDate(project.createdAt)}
                        </span>
                      </div>
                      <div className="project-status">
                        {getStatusBadge(project.status)}
                      </div>
                    </div>
                  </div>
                ))}
              </div>
            ) : (
              <div className="empty-state">
                <div className="empty-icon">📋</div>
                <h3>Brak projektów</h3>
                <p>Rozpocznij swoją przygodę tworząc pierwszy projekt!</p>
                <Link to="/projects" className="btn btn-primary">
                  Stwórz projekt
                </Link>
              </div>
            )}
          </div>
        </div>

        {/* Szybkie akcje */}
        <div className="dashboard-section">
          <div className="section-header">
            <h2 className="section-title">⚡ Szybkie akcje</h2>
          </div>
          
          <div className="quick-actions">
            <Link to="/projects/new" className="action-card">
              <div className="action-icon">➕</div>
              <div className="action-content">
                <h3>Nowy projekt</h3>
                <p>Stwórz nowy projekt</p>
              </div>
            </Link>
            
            <Link to="/projects" className="action-card">
              <div className="action-icon">📁</div>
              <div className="action-content">
                <h3>Przeglądaj projekty</h3>
                <p>Zobacz wszystkie projekty</p>
              </div>
            </Link>
            
            <Link to="/profile" className="action-card">
              <div className="action-icon">👤</div>
              <div className="action-content">
                <h3>Edytuj profil</h3>
                <p>Zaktualizuj swoje dane</p>
              </div>
            </Link>
            
            {user?.role === 'admin' && (
              <Link to="/admin" className="action-card">
                <div className="action-icon">⚙️</div>
                <div className="action-content">
                  <h3>Panel admina</h3>
                  <p>Zarządzaj systemem</p>
                </div>
              </Link>
            )}
          </div>
        </div>
      </div>
    </div>
  );
};

export default Dashboard;