import React, { useState, useEffect } from 'react';
import { useParams, useNavigate, Link } from 'react-router-dom';

const ProjectDetail = () => {
  const { id } = useParams();
  const navigate = useNavigate();
  const [project, setProject] = useState(null);
  const [comments, setComments] = useState([]);
  const [loading, setLoading] = useState(true);
  const [commentsLoading, setCommentsLoading] = useState(false);
  const [newComment, setNewComment] = useState('');
  const [editingComment, setEditingComment] = useState(null);
  const [editCommentText, setEditCommentText] = useState('');
  const [user, setUser] = useState(null);

  useEffect(() => {
    const userData = localStorage.getItem('user');
    if (userData) {
      setUser(JSON.parse(userData));
    }
    fetchProject();
    fetchComments();
  }, [id]);

  const fetchProject = async () => {
    try {
      const token = localStorage.getItem('token');
      const response = await fetch(`/api/projects/${id}`, {
        headers: {
          'Authorization': `Bearer ${token}`
        }
      });
      
      if (response.ok) {
        const data = await response.json();
        setProject(data);
      } else if (response.status === 404) {
        navigate('/projects');
      } else {
        console.error('Error fetching project');
      }
    } catch (error) {
      console.error('Error fetching project:', error);
    } finally {
      setLoading(false);
    }
  };

  const fetchComments = async () => {
    try {
      setCommentsLoading(true);
      const response = await fetch(`/api/projects/${id}/comments?limit=50`);
      
      if (response.ok) {
        const data = await response.json();
        setComments(data.results || []);
      }
    } catch (error) {
      console.error('Error fetching comments:', error);
    } finally {
      setCommentsLoading(false);
    }
  };

  const handleAddComment = async (e) => {
    e.preventDefault();
    if (!newComment.trim()) return;

    try {
      const token = localStorage.getItem('token');
      const response = await fetch(`/api/projects/${id}/comments`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${token}`
        },
        body: JSON.stringify({ text: newComment })
      });

      if (response.ok) {
        setNewComment('');
        fetchComments();
      } else {
        alert('Błąd podczas dodawania komentarza');
      }
    } catch (error) {
      console.error('Error adding comment:', error);
      alert('Błąd podczas dodawania komentarza');
    }
  };

  const handleEditComment = async (commentId) => {
    if (!editCommentText.trim()) return;

    try {
      const token = localStorage.getItem('token');
      const response = await fetch(`/api/projects/${id}/comments/${commentId}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${token}`
        },
        body: JSON.stringify({ text: editCommentText })
      });

      if (response.ok) {
        setEditingComment(null);
        setEditCommentText('');
        fetchComments();
      } else {
        alert('Błąd podczas edycji komentarza');
      }
    } catch (error) {
      console.error('Error editing comment:', error);
      alert('Błąd podczas edycji komentarza');
    }
  };

  const handleDeleteComment = async (commentId) => {
    if (!window.confirm('Czy na pewno chcesz usunąć ten komentarz?')) {
      return;
    }

    try {
      const token = localStorage.getItem('token');
      const response = await fetch(`/api/projects/${id}/comments/${commentId}`, {
        method: 'DELETE',
        headers: {
          'Authorization': `Bearer ${token}`
        }
      });

      if (response.ok) {
        fetchComments();
      } else {
        alert('Błąd podczas usuwania komentarza');
      }
    } catch (error) {
      console.error('Error deleting comment:', error);
      alert('Błąd podczas usuwania komentarza');
    }
  };

  const canEditProject = () => {
    // Add null check for project and project.owner
    return user && project && project.owner && (user.role === 'admin' || project.owner._id === user.id);
  };

  const canEditComment = (comment) => {
    return user && comment && comment.author && (user.role === 'admin' || comment.author._id === user.id);
  };

  const canDeleteComment = (comment) => {
    return user && comment && comment.author && project && project.owner && 
           (user.role === 'admin' || comment.author._id === user.id || project.owner._id === user.id);
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
      year: 'numeric',
      hour: '2-digit',
      minute: '2-digit'
    });
  };

  if (loading) {
    return (
      <div className="loading">
        <div className="loading-spinner">⏳</div>
        <p>Ładowanie projektu...</p>
      </div>
    );
  }

  if (!project) {
    return (
      <div className="empty-state">
        <div className="empty-icon">❌</div>
        <h3>Projekt nie został znaleziony</h3>
        <Link to="/projects" className="btn btn-primary">
          ← Powrót do projektów
        </Link>
      </div>
    );
  }

  return (
    <div className="projects-page">
      <div className="dashboard-header">
        {canEditProject() && (
          <Link 
            to={`/projects/${project._id}/edit`}
            className="btn btn-primary"
          >
            ✏️ Edytuj projekt
          </Link>
        )}
      </div>

      <div className="dashboard-content">
        {/* Informacje o projekcie */}
        <div className="dashboard-section">
          <div className="section-header">
            <h1 className="page-title">{project.name}</h1>
            {getStatusBadge(project.status)}
          </div>
          
          <div className="section-content">
            <div className="stats-grid">
              <div className="stat-card">
                <div className="stat-icon">🏷️</div>
                <div className="stat-content">
                  <div className="stat-label">Kategoria</div>
                  <div className="stat-number">{project.category}</div>
                </div>
              </div>
              
              <div className="stat-card">
                <div className="stat-icon">👤</div>
                <div className="stat-content">
                  <div className="stat-label">Właściciel</div>
                  <div className="stat-number">{project.owner?.name}</div>
                </div>
              </div>
              
              <div className="stat-card">
                <div className="stat-icon">📅</div>
                <div className="stat-content">
                  <div className="stat-label">Data utworzenia</div>
                  <div className="stat-number">{formatDate(project.createdAt)}</div>
                </div>
              </div>
              
              <div className="stat-card">
                <div className="stat-icon">💬</div>
                <div className="stat-content">
                  <div className="stat-label">Komentarze</div>
                  <div className="stat-number">{comments.length}</div>
                </div>
              </div>
            </div>
          </div>
        </div>

        {/* Opis projektu */}
        <div className="dashboard-section">
          <div className="section-header">
            <h2 className="section-title">📋 Opis projektu</h2>
          </div>
          
          <div className="section-content">
            {project.description ? (
              <div className="project-description">
                <p>{project.description}</p>
              </div>
            ) : (
              <div className="empty-state">
                <div className="empty-icon">📝</div>
                <h3>Brak opisu</h3>
                <p>Ten projekt nie ma jeszcze opisu.</p>
              </div>
            )}
          </div>
        </div>

        {/* Sekcja komentarzy */}
        <div className="dashboard-section">
          <div className="section-header">
            <h2 className="section-title">💬 Komentarze ({comments.length})</h2>
          </div>
          
          <div className="section-content">
            {/* Formularz dodawania komentarza */}
            {user ? (
              <form onSubmit={handleAddComment} className="comment-form">
                <textarea
                  value={newComment}
                  onChange={(e) => setNewComment(e.target.value)}
                  placeholder="Dodaj komentarz..."
                  className="comment-textarea"
                  rows="3"
                />
                <div className="form-actions">
                  <button 
                    type="submit" 
                    className="btn btn-primary"
                    disabled={!newComment.trim()}
                  >
                    💬 Dodaj komentarz
                  </button>
                </div>
              </form>
            ) : (
              <div className="empty-state">
                <div className="empty-icon">🔐</div>
                <h3>Wymagane logowanie</h3>
                <p>
                  <Link to="/login">Zaloguj się</Link>, aby dodać komentarz
                </p>
              </div>
            )}

            {/* Lista komentarzy */}
            {commentsLoading ? (
              <div className="loading">
                <div className="loading-spinner">⏳</div>
                <p>Ładowanie komentarzy...</p>
              </div>
            ) : comments.length > 0 ? (
              <div className="comments-list">
                {comments.map(comment => (
                  <div key={comment._id} className="comment-item">
                    <div className="comment-header">
                      <div className="comment-author">
                        <span className="author-icon">👤</span>
                        <span className="author-name">{comment.author?.name}</span>
                        <span className="comment-date">📅 {formatDate(comment.createdAt)}</span>
                      </div>
                      {(canEditComment(comment) || canDeleteComment(comment)) && (
                        <div className="comment-actions">
                          {canEditComment(comment) && (
                            <button
                              onClick={() => {
                                setEditingComment(comment._id);
                                setEditCommentText(comment.text);
                              }}
                              className="btn btn-secondary"
                              style={{ padding: '4px 8px', fontSize: '12px' }}
                            >
                              ✏️
                            </button>
                          )}
                          {canDeleteComment(comment) && (
                            <button
                              onClick={() => handleDeleteComment(comment._id)}
                              className="btn btn-secondary"
                              style={{ padding: '4px 8px', fontSize: '12px', marginLeft: '4px' }}
                            >
                              🗑️
                            </button>
                          )}
                        </div>
                      )}
                    </div>
                    
                    <div className="comment-content">
                      {editingComment === comment._id ? (
                        <div className="edit-comment-form">
                          <textarea
                            value={editCommentText}
                            onChange={(e) => setEditCommentText(e.target.value)}
                            className="comment-textarea"
                            rows="3"
                          />
                          <div className="form-actions">
                            <button
                              onClick={() => handleEditComment(comment._id)}
                              className="btn btn-primary"
                              disabled={!editCommentText.trim()}
                            >
                              💾 Zapisz
                            </button>
                            <button
                              onClick={() => {
                                setEditingComment(null);
                                setEditCommentText('');
                              }}
                              className="btn btn-secondary"
                            >
                              ❌ Anuluj
                            </button>
                          </div>
                        </div>
                      ) : (
                        <p>{comment.text}</p>
                      )}
                    </div>
                  </div>
                ))}
              </div>
            ) : (
              <div className="empty-state">
                <div className="empty-icon">💬</div>
                <h3>Brak komentarzy</h3>
                <p>Bądź pierwszy, który skomentuje ten projekt!</p>
              </div>
            )}
          </div>
        </div>
      </div>
    </div>
  );
};

export default ProjectDetail;
