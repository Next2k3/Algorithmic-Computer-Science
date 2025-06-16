import React, { useState, useEffect } from 'react';
import { Link, useNavigate } from 'react-router-dom';

const Projects = () => {
  const [projects, setProjects] = useState([]);
  const [loading, setLoading] = useState(true);
  const [filters, setFilters] = useState({
    category: '',
    status: '',
    search: ''
  });
  const [pagination, setPagination] = useState({
    page: 1,
    limit: 10,
    total: 0,
    totalPages: 0
  });
  const [user, setUser] = useState(null);
  const navigate = useNavigate();

  useEffect(() => {
    const userData = localStorage.getItem('user');
    if (userData) {
      setUser(JSON.parse(userData));
    }
    fetchProjects();
  }, [filters, pagination.page]);

  const fetchProjects = async () => {
    try {
      setLoading(true);
      const token = localStorage.getItem('token');
      
      const params = new URLSearchParams({
        page: pagination.page,
        limit: pagination.limit,
        sortBy: 'createdAt',
        sortOrder: 'desc'
      });
      
      if (filters.category) params.append('category', filters.category);
      if (filters.status) params.append('status', filters.status);
      
      const response = await fetch(`/api/projects?${params}`, {
        headers: {
          'Authorization': `Bearer ${token}`
        }
      });
      
      const data = await response.json();
      
      if (data.results) {
        let filteredProjects = data.results;
        
        // Filtrowanie po wyszukiwaniu (lokalnie)
        if (filters.search) {
          filteredProjects = data.results.filter(project =>
            project.name.toLowerCase().includes(filters.search.toLowerCase()) ||
            project.description?.toLowerCase().includes(filters.search.toLowerCase())
          );
        }
        
        setProjects(filteredProjects);
        setPagination(prev => ({
          ...prev,
          total: data.total,
          totalPages: data.totalPages
        }));
      }
    } catch (error) {
      console.error('Error fetching projects:', error);
    } finally {
      setLoading(false);
    }
  };

  const handleFilterChange = (key, value) => {
    setFilters(prev => ({ ...prev, [key]: value }));
    setPagination(prev => ({ ...prev, page: 1 }));
  };

  const handleDelete = async (projectId) => {
    if (!window.confirm('Czy na pewno chcesz usunąć ten projekt?')) {
      return;
    }
    
    try {
      const token = localStorage.getItem('token');
      const response = await fetch(`/api/projects/${projectId}`, {
        method: 'DELETE',
        headers: {
          'Authorization': `Bearer ${token}`
        }
      });
      
      if (response.ok) {
        fetchProjects(); // Odśwież listę
      } else {
        alert('Błąd podczas usuwania projektu');
      }
    } catch (error) {
      console.error('Error deleting project:', error);
      alert('Błąd podczas usuwania projektu');
    }
  };

  const canEditProject = (project) => {
    return user?.role === 'admin' || project.owner?._id === user?.id;
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

  const handlePageChange = (newPage) => {
    setPagination(prev => ({ ...prev, page: newPage }));
  };

  return (
    <div className="projects-page">
      <div className="dashboard-header">
        <h1 className="page-title">📁 Projekty</h1>
        <Link to="/projects/new" className="btn btn-primary">
          ➕ Nowy projekt
        </Link>
      </div>

      <div className="dashboard-content">
        {/* Filtry */}
        <div className="dashboard-section">
          <div className="section-header">
            <h2 className="section-title">🔍 Wyszukiwanie i filtry</h2>
          </div>
          
          <div className="section-content">
            <div className="stats-grid">
              <div className="stat-card">
                <div className="stat-icon">🔍</div>
                <div className="stat-content">
                  <div className="stat-label">Wyszukaj</div>
                  <input
                    type="text"
                    className="form-input"
                    placeholder="Nazwa lub opis projektu..."
                    value={filters.search}
                    onChange={(e) => handleFilterChange('search', e.target.value)}
                  />
                </div>
              </div>
              
              <div className="stat-card">
                <div className="stat-icon">🏷️</div>
                <div className="stat-content">
                  <div className="stat-label">Kategoria</div>
                  <select
                    className="form-input"
                    value={filters.category}
                    onChange={(e) => handleFilterChange('category', e.target.value)}
                  >
                    <option value="">Wszystkie kategorie</option>
                    <option value="web">Web Development</option>
                    <option value="mobile">Mobile App</option>
                    <option value="design">Design</option>
                    <option value="marketing">Marketing</option>
                    <option value="other">Inne</option>
                  </select>
                </div>
              </div>
              
              <div className="stat-card">
                <div className="stat-icon">📊</div>
                <div className="stat-content">
                  <div className="stat-label">Status</div>
                  <select
                    className="form-input"
                    value={filters.status}
                    onChange={(e) => handleFilterChange('status', e.target.value)}
                  >
                    <option value="">Wszystkie statusy</option>
                    <option value="active">Aktywny</option>
                    <option value="completed">Zakończony</option>
                    <option value="on-hold">Wstrzymany</option>
                  </select>
                </div>
              </div>
              
              <div className="stat-card">
                <div className="stat-icon">📈</div>
                <div className="stat-content">
                  <div className="stat-label">Znaleziono</div>
                  <div className="stat-number">{projects.length}</div>
                </div>
              </div>
            </div>
          </div>
        </div>

        {/* Lista projektów */}
        <div className="dashboard-section">
          <div className="section-header">
            <h2 className="section-title">📋 Lista projektów</h2>
            <Link to="/projects/new" className="section-link">
              ➕ Dodaj nowy →
            </Link>
          </div>
          
          <div className="section-content">
            {loading ? (
              <div className="loading">
                <div className="loading-spinner">⏳</div>
                <p>Ładowanie projektów...</p>
              </div>
            ) : projects.length > 0 ? (
              <>
                <div className="projects-list">
                  {projects.map(project => (
                    <div key={project._id} className="project-item">
                      <div className="project-main">
                        <h3 className="project-title">
                          <Link to={`/projects/${project._id}`}>
                            {project.name}
                          </Link>
                        </h3>
                        <p className="project-description">
                          {project.description || 'Brak opisu projektu'}
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
                      
                      {canEditProject(project) && (
                        <div className="project-actions">
                          <button
			    onClick={() => navigate(`/projects/${project._id}/edit`)}
			    className="btn btn-secondary"
			  >
			    ✏️ Edytuj
			  </button>
                          <button
                            onClick={() => handleDelete(project._id)}
                            className="btn btn-secondary"
                            style={{ marginLeft: '8px' }}
                          >
                            🗑️ Usuń
                          </button>
                        </div>
                      )}
                    </div>
                  ))}
                </div>

                {/* Paginacja */}
                {pagination.totalPages > 1 && (
                  <div className="dashboard-section">
                    <div className="section-header">
                      <h2 className="section-title">📄 Paginacja</h2>
                    </div>
                    
                    <div className="section-content">
                      <div className="quick-actions">
                        <button
                          onClick={() => handlePageChange(pagination.page - 1)}
                          disabled={pagination.page === 1}
                          className="action-card"
                          style={{ opacity: pagination.page === 1 ? 0.5 : 1 }}
                        >
                          <div className="action-icon">⬅️</div>
                          <div className="action-content">
                            <h3>Poprzednia</h3>
                            <p>Strona {pagination.page - 1}</p>
                          </div>
                        </button>
                        
                        <div className="action-card" style={{ textAlign: 'center' }}>
                          <div className="action-icon">📄</div>
                          <div className="action-content">
                            <h3>Strona {pagination.page}</h3>
                            <p>z {pagination.totalPages}</p>
                          </div>
                        </div>
                        
                        <button
                          onClick={() => handlePageChange(pagination.page + 1)}
                          disabled={pagination.page === pagination.totalPages}
                          className="action-card"
                          style={{ opacity: pagination.page === pagination.totalPages ? 0.5 : 1 }}
                        >
                          <div className="action-icon">➡️</div>
                          <div className="action-content">
                            <h3>Następna</h3>
                            <p>Strona {pagination.page + 1}</p>
                          </div>
                        </button>
                      </div>
                    </div>
                  </div>
                )}
              </>
            ) : (
              <div className="empty-state">
                <div className="empty-icon">📋</div>
                <h3>Brak projektów</h3>
                <p>
                  {filters.search || filters.category || filters.status
                    ? 'Nie znaleziono projektów spełniających kryteria wyszukiwania.'
                    : 'Nie masz jeszcze żadnych projektów. Stwórz swój pierwszy projekt!'
                  }
                </p>
                {!filters.search && !filters.category && !filters.status && (
                  <Link to="/projects/new" className="btn btn-primary">
                    ➕ Stwórz pierwszy projekt
                  </Link>
                )}
              </div>
            )}
          </div>
        </div>
      </div>
    </div>
  );
};

export default Projects;
