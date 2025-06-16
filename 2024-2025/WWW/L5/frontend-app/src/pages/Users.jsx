import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';

const Users = () => {
  const [users, setUsers] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState('');
  const [user, setUser] = useState(null);

  useEffect(() => {
    const userData = localStorage.getItem('user');
    if (userData) {
      const parsedUser = JSON.parse(userData);
      setUser(parsedUser);
      
      // Sprawdź czy użytkownik jest adminem
      if (parsedUser.role !== 'admin') {
        setError('Brak uprawnień do przeglądania listy użytkowników');
        setLoading(false);
        return;
      }
      
      fetchUsers();
    } else {
      setError('Musisz być zalogowany aby przeglądać użytkowników');
      setLoading(false);
    }
  }, []);

  const fetchUsers = async () => {
    try {
      const token = localStorage.getItem('token');
      const response = await fetch('/api/users', {
        headers: {
          'Authorization': `Bearer ${token}`
        }
      });

      if (response.ok) {
        const data = await response.json();
        setUsers(data);
      } else if (response.status === 403) {
        setError('Brak uprawnień do przeglądania użytkowników');
      } else {
        setError('Błąd podczas pobierania listy użytkowników');
      }
    } catch (error) {
      console.error('Error fetching users:', error);
      setError('Błąd połączenia z serwerem');
    } finally {
      setLoading(false);
    }
  };

  const handleDeleteUser = async (userId, userName) => {
    if (!window.confirm(`Czy na pewno chcesz usunąć użytkownika ${userName}?`)) {
      return;
    }

    try {
      const token = localStorage.getItem('token');
      const response = await fetch(`/api/users/${userId}`, {
        method: 'DELETE',
        headers: {
          'Authorization': `Bearer ${token}`
        }
      });

      if (response.ok) {
        // Usuń użytkownika z lokalnej listy
        setUsers(users.filter(u => u._id !== userId));
      } else {
        alert('Błąd podczas usuwania użytkownika');
      }
    } catch (error) {
      console.error('Error deleting user:', error);
      alert('Błąd podczas usuwania użytkownika');
    }
  };

  const handleRoleChange = async (userId, newRole) => {
    try {
      const token = localStorage.getItem('token');
      const userToUpdate = users.find(u => u._id === userId);
      
      const response = await fetch(`/api/users/${userId}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${token}`
        },
        body: JSON.stringify({
          name: userToUpdate.name,
          email: userToUpdate.email,
          role: newRole
        })
      });

      if (response.ok) {
        const updatedUser = await response.json();
        setUsers(users.map(u => u._id === userId ? updatedUser : u));
      } else {
        alert('Błąd podczas zmiany roli użytkownika');
      }
    } catch (error) {
      console.error('Error updating user role:', error);
      alert('Błąd podczas zmiany roli użytkownika');
    }
  };

  const getRoleBadge = (role) => {
    const statusClasses = {
      'admin': 'status-badge status-active',
      'user': 'status-badge status-completed'
    };
    
    const roleLabels = {
      'admin': 'Administrator',
      'user': 'Użytkownik'
    };
    
    return (
      <span className={statusClasses[role]}>
        {roleLabels[role]}
      </span>
    );
  };

  const formatDate = (dateString) => {
    return new Date(dateString).toLocaleDateString('pl-PL', {
      day: '2-digit',
      month: '2-digit',
      year: 'numeric',
      hour: '2-digit',
      minute: '2-digit'
    });
  };

  if (loading) {
    return (
      <div className="loading">
        <div className="loading-spinner">⏳</div>
        <p>Ładowanie użytkowników...</p>
      </div>
    );
  }

  if (error) {
    return (
      <div className="empty-state">
        <div className="empty-icon">❌</div>
        <h3>Błąd dostępu</h3>
        <p>{error}</p>
        <Link to="/dashboard" className="btn btn-primary">
          ← Powrót do dashboardu
        </Link>
      </div>
    );
  }

  return (
    <div className="dashboard">
      <div className="dashboard-header">
        <h1 className="page-title">
          👥 Zarządzanie użytkownikami
        </h1>
        <p className="dashboard-subtitle">
          Zarządzaj użytkownikami systemu i ich uprawnieniami
        </p>
      </div>

      {/* Statystyki użytkowników */}
      <div className="stats-grid">
        <div className="stat-card">
          <div className="stat-icon">👥</div>
          <div className="stat-content">
            <div className="stat-number">{users.length}</div>
            <div className="stat-label">Wszyscy użytkownicy</div>
          </div>
        </div>
        
        <div className="stat-card">
          <div className="stat-icon">👑</div>
          <div className="stat-content">
            <div className="stat-number">{users.filter(u => u.role === 'admin').length}</div>
            <div className="stat-label">Administratorzy</div>
          </div>
        </div>
        
        <div className="stat-card">
          <div className="stat-icon">👤</div>
          <div className="stat-content">
            <div className="stat-number">{users.filter(u => u.role === 'user').length}</div>
            <div className="stat-label">Zwykli użytkownicy</div>
          </div>
        </div>
        
        <div className="stat-card">
          <div className="stat-icon">📅</div>
          <div className="stat-content">
            <div className="stat-number">
              {users.filter(u => {
                const oneWeekAgo = new Date();
                oneWeekAgo.setDate(oneWeekAgo.getDate() - 7);
                return new Date(u.createdAt) > oneWeekAgo;
              }).length}
            </div>
            <div className="stat-label">Nowi (7 dni)</div>
          </div>
        </div>
      </div>

      <div className="dashboard-content">
        {/* Lista użytkowników */}
        <div className="dashboard-section">
          <div className="section-header">
            <h2 className="section-title">👥 Lista użytkowników</h2>
          </div>
          
          <div className="section-content">
            {users.length > 0 ? (
              <div className="projects-list">
                {users.map(userItem => (
                  <div key={userItem._id} className="project-item">
                    <div className="project-main">
                      <h3 className="project-title">
                        <Link to={`/users/${userItem._id}`}>
                          {userItem.name}
                        </Link>
                        {userItem._id === user?.id && (
                          <span className="status-badge status-on-hold" style={{marginLeft: '8px', fontSize: '12px'}}>
                            To Ty
                          </span>
                        )}
                      </h3>
                      <p className="project-description">
                        📧 {userItem.email}
                      </p>
                    </div>
                    <div className="project-meta">
                      <div className="project-details">
                        <span className="project-category">
                          🏷️ {getRoleBadge(userItem.role)}
                        </span>
                        <span className="project-date">
                          📅 {formatDate(userItem.createdAt)}
                        </span>
                      </div>
                      <div className="project-actions">
                        <select
                          value={userItem.role}
                          onChange={(e) => handleRoleChange(userItem._id, e.target.value)}
                          className="btn btn-secondary"
                          style={{marginRight: '8px', fontSize: '14px'}}
                          disabled={userItem._id === user?.id}
                        >
                          <option value="user">Użytkownik</option>
                          <option value="admin">Administrator</option>
                        </select>
                        

                        
                        {userItem._id !== user?.id && (
                          <button
                            onClick={() => handleDeleteUser(userItem._id, userItem.name)}
                            className="btn btn-primary"
                            style={{backgroundColor: '#dc3545', borderColor: '#dc3545'}}
                            title="Usuń użytkownika"
                          >
                            🗑️ Usuń
                          </button>
                        )}
                      </div>
                    </div>
                  </div>
                ))}
              </div>
            ) : (
              <div className="empty-state">
                <div className="empty-icon">👥</div>
                <h3>Brak użytkowników</h3>
                <p>Nie znaleziono żadnych użytkowników w systemie.</p>
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
            <Link to="/dashboard" className="action-card">
              <div className="action-icon">🏠</div>
              <div className="action-content">
                <h3>Dashboard</h3>
                <p>Powrót do głównego panelu</p>
              </div>
            </Link>
            
            <Link to="/projects" className="action-card">
              <div className="action-icon">📁</div>
              <div className="action-content">
                <h3>Projekty</h3>
                <p>Zarządzaj projektami</p>
              </div>
            </Link>
            
            <Link to="/admin" className="action-card">
              <div className="action-icon">⚙️</div>
              <div className="action-content">
                <h3>Panel admina</h3>
                <p>Inne funkcje administracyjne</p>
              </div>
            </Link>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Users;
