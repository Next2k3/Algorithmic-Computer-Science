import React, { useState, useEffect } from 'react';
import { useParams, useNavigate } from 'react-router-dom';

const ProjectEdit = () => {
  const { id } = useParams();
  const navigate = useNavigate();
  
  const [formData, setFormData] = useState({
    name: '',
    description: '',
    category: '',
    status: 'active'
  });
  const [loading, setLoading] = useState(false);
  const [initialLoading, setInitialLoading] = useState(true);
  const [error, setError] = useState('');
  const [project, setProject] = useState(null);

  useEffect(() => {
    fetchProject();
  }, [id]);

  const fetchProject = async () => {
    try {
      setInitialLoading(true);
      const token = localStorage.getItem('token');
      const response = await fetch(`/api/projects/${id}`, {
        headers: {
          'Authorization': `Bearer ${token}`
        }
      });

      if (response.ok) {
        const projectData = await response.json();
        setProject(projectData);
        setFormData({
          name: projectData.name || '',
          description: projectData.description || '',
          category: projectData.category || '',
          status: projectData.status || 'active'
        });
      } else {
        setError('Nie udało się pobrać danych projektu');
      }
    } catch (error) {
      console.error('Error fetching project:', error);
      setError('Błąd połączenia z serwerem');
    } finally {
      setInitialLoading(false);
    }
  };

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);
    setError('');

    try {
      const token = localStorage.getItem('token');
      const response = await fetch(`/api/projects/${id}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${token}`
        },
        body: JSON.stringify(formData)
      });

      const data = await response.json();

      if (response.ok) {
        // Redirect to project detail page
        navigate(`/projects/${id}`);
      } else {
        setError(data.error || 'Błąd podczas aktualizacji projektu');
      }
    } catch (error) {
      console.error('Error updating project:', error);
      setError('Błąd połączenia z serwerem');
    } finally {
      setLoading(false);
    }
  };

  const handleCancel = () => {
    navigate(`/projects/${id}`);
  };

  const handleBackToProjects = () => {
    navigate('/projects');
  };

  // Sprawdź czy dane się zmieniły
  const hasChanges = project && (
    formData.name !== project.name ||
    formData.description !== (project.description || '') ||
    formData.category !== project.category ||
    formData.status !== project.status
  );

  if (initialLoading) {
    return (
      <div style={{ 
        maxWidth: '800px', 
        margin: '0 auto', 
        padding: '20px',
        fontFamily: 'system-ui, -apple-system, sans-serif',
        textAlign: 'center'
      }}>
        <div style={{
          backgroundColor: 'white',
          padding: '60px',
          borderRadius: '12px',
          boxShadow: '0 4px 6px -1px rgba(0, 0, 0, 0.1)',
          border: '1px solid #e5e7eb'
        }}>
          <div style={{ fontSize: '3rem', marginBottom: '20px' }}>⏳</div>
          <h2 style={{ color: '#374151', marginBottom: '10px' }}>Ładowanie projektu...</h2>
          <p style={{ color: '#6b7280' }}>Pobieranie danych projektu do edycji</p>
        </div>
      </div>
    );
  }

  if (error && !project) {
    return (
      <div style={{ 
        maxWidth: '800px', 
        margin: '0 auto', 
        padding: '20px',
        fontFamily: 'system-ui, -apple-system, sans-serif'
      }}>
        <div style={{
          backgroundColor: '#fee2e2',
          border: '1px solid #fecaca',
          color: '#dc2626',
          padding: '30px',
          borderRadius: '12px',
          textAlign: 'center'
        }}>
          <div style={{ fontSize: '3rem', marginBottom: '20px' }}>❌</div>
          <h2 style={{ marginBottom: '10px' }}>Błąd ładowania</h2>
          <p style={{ marginBottom: '20px' }}>{error}</p>
          <button 
            onClick={handleBackToProjects}
            style={{
              padding: '12px 24px',
              backgroundColor: '#dc2626',
              color: 'white',
              border: 'none',
              borderRadius: '8px',
              cursor: 'pointer'
            }}
          >
            ← Powrót do projektów
          </button>
        </div>
      </div>
    );
  }

  return (
    <div style={{ 
      maxWidth: '800px', 
      margin: '0 auto', 
      padding: '20px',
      fontFamily: 'system-ui, -apple-system, sans-serif'
    }}>
      {/* Header */}
      <div style={{ 
        display: 'flex', 
        justifyContent: 'space-between', 
        alignItems: 'center',
        marginBottom: '30px',
        paddingBottom: '20px',
        borderBottom: '2px solid #e5e7eb'
      }}>
        <div>
          <h1 style={{ 
            fontSize: '2rem',
            fontWeight: 'bold',
            color: '#1f2937',
            margin: 0,
            marginBottom: '5px'
          }}>
            ✏️ Edytuj projekt
          </h1>
          <p style={{
            color: '#6b7280',
            margin: 0,
            fontSize: '1rem'
          }}>
            {project?.name}
          </p>
        </div>
        <div style={{ display: 'flex', gap: '10px' }}>
          <button 
            onClick={handleBackToProjects}
            style={{
              padding: '10px 20px',
              backgroundColor: '#6b7280',
              color: 'white',
              border: 'none',
              borderRadius: '8px',
              cursor: 'pointer'
            }}
          >
            📁 Wszystkie projekty
          </button>
          <button 
            onClick={handleCancel}
            style={{
              padding: '10px 20px',
              backgroundColor: '#3b82f6',
              color: 'white',
              border: 'none',
              borderRadius: '8px',
              cursor: 'pointer'
            }}
          >
            👁️ Podgląd projektu
          </button>
        </div>
      </div>

      {/* Error Message */}
      {error && (
        <div style={{
          backgroundColor: '#fee2e2',
          border: '1px solid #fecaca',
          color: '#dc2626',
          padding: '15px',
          borderRadius: '8px',
          marginBottom: '20px'
        }}>
          ❌ {error}
        </div>
      )}

      {/* Changes Indicator */}
      {hasChanges && (
        <div style={{
          backgroundColor: '#fef3c7',
          border: '1px solid #fbbf24',
          color: '#92400e',
          padding: '15px',
          borderRadius: '8px',
          marginBottom: '20px'
        }}>
          ⚠️ Masz niezapisane zmiany w formularzu
        </div>
      )}
      
      {/* Form Section */}
      <div style={{
        backgroundColor: 'white',
        padding: '30px',
        borderRadius: '12px',
        boxShadow: '0 4px 6px -1px rgba(0, 0, 0, 0.1)',
        border: '1px solid #e5e7eb',
        marginBottom: '30px'
      }}>
        <h2 style={{ 
          fontSize: '1.5rem',
          fontWeight: 'semibold',
          color: '#374151',
          marginBottom: '20px'
        }}>
          📝 Szczegóły projektu
        </h2>
        
        <div style={{ maxWidth: '600px' }}>
          {/* Project Name */}
          <div style={{ marginBottom: '20px' }}>
            <label style={{
              display: 'block',
              fontSize: '0.875rem',
              fontWeight: 'medium',
              color: '#374151',
              marginBottom: '8px'
            }}>
              📋 Nazwa projektu *
            </label>
            <input
              type="text"
              name="name"
              value={formData.name}
              onChange={handleInputChange}
              placeholder="Wprowadź nazwę projektu..."
              required
              style={{
                width: '100%',
                padding: '12px',
                border: '2px solid #d1d5db',
                borderRadius: '8px',
                fontSize: '1rem',
                outline: 'none',
                transition: 'border-color 0.2s'
              }}
              onFocus={(e) => e.target.style.borderColor = '#3b82f6'}
              onBlur={(e) => e.target.style.borderColor = '#d1d5db'}
            />
          </div>

          {/* Description */}
          <div style={{ marginBottom: '20px' }}>
            <label style={{
              display: 'block',
              fontSize: '0.875rem',
              fontWeight: 'medium',
              color: '#374151',
              marginBottom: '8px'
            }}>
              📄 Opis projektu
            </label>
            <textarea
              name="description"
              value={formData.description}
              onChange={handleInputChange}
              placeholder="Opisz swój projekt..."
              rows={4}
              style={{
                width: '100%',
                padding: '12px',
                border: '2px solid #d1d5db',
                borderRadius: '8px',
                fontSize: '1rem',
                outline: 'none',
                resize: 'vertical',
                minHeight: '100px'
              }}
              onFocus={(e) => e.target.style.borderColor = '#3b82f6'}
              onBlur={(e) => e.target.style.borderColor = '#d1d5db'}
            />
          </div>

          {/* Category */}
          <div style={{ marginBottom: '20px' }}>
            <label style={{
              display: 'block',
              fontSize: '0.875rem',
              fontWeight: 'medium',
              color: '#374151',
              marginBottom: '8px'
            }}>
              🏷️ Kategoria *
            </label>
            <select
              name="category"
              value={formData.category}
              onChange={handleInputChange}
              required
              style={{
                width: '100%',
                padding: '12px',
                border: '2px solid #d1d5db',
                borderRadius: '8px',
                fontSize: '1rem',
                outline: 'none',
                backgroundColor: 'white'
              }}
            >
              <option value="">Wybierz kategorię...</option>
              <option value="web">Web Development</option>
              <option value="mobile">Mobile App</option>
              <option value="design">Design</option>
              <option value="marketing">Marketing</option>
              <option value="other">Inne</option>
            </select>
          </div>

          {/* Status */}
          <div style={{ marginBottom: '30px' }}>
            <label style={{
              display: 'block',
              fontSize: '0.875rem',
              fontWeight: 'medium',
              color: '#374151',
              marginBottom: '8px'
            }}>
              📊 Status projektu
            </label>
            <select
              name="status"
              value={formData.status}
              onChange={handleInputChange}
              style={{
                width: '100%',
                padding: '12px',
                border: '2px solid #d1d5db',
                borderRadius: '8px',
                fontSize: '1rem',
                outline: 'none',
                backgroundColor: 'white'
              }}
            >
              <option value="active">Aktywny</option>
              <option value="completed">Zakończony</option>
              <option value="on-hold">Wstrzymany</option>
            </select>
          </div>

          {/* Action Buttons */}
          <div style={{ 
            display: 'flex', 
            gap: '15px',
            justifyContent: 'flex-end'
          }}>
            <button
              type="button"
              onClick={handleCancel}
              disabled={loading}
              style={{
                padding: '12px 24px',
                backgroundColor: '#6b7280',
                color: 'white',
                border: 'none',
                borderRadius: '8px',
                fontSize: '1rem',
                cursor: loading ? 'not-allowed' : 'pointer',
                opacity: loading ? 0.6 : 1
              }}
            >
              ❌ Anuluj
            </button>
            <button
              type="button"
              onClick={handleSubmit}
              disabled={loading || !formData.name || !formData.category || !hasChanges}
              style={{
                padding: '12px 24px',
                backgroundColor: (!formData.name || !formData.category || !hasChanges) ? '#9ca3af' : '#10b981',
                color: 'white',
                border: 'none',
                borderRadius: '8px',
                fontSize: '1rem',
                cursor: (loading || !formData.name || !formData.category || !hasChanges) ? 'not-allowed' : 'pointer'
              }}
            >
              {loading ? '⏳ Zapisuję...' : '💾 Zapisz zmiany'}
            </button>
          </div>
        </div>
      </div>

      {/* Preview Section */}
      <div style={{
        backgroundColor: 'white',
        padding: '30px',
        borderRadius: '12px',
        boxShadow: '0 4px 6px -1px rgba(0, 0, 0, 0.1)',
        border: '1px solid #e5e7eb',
        marginBottom: '30px'
      }}>
        <h2 style={{ 
          fontSize: '1.5rem',
          fontWeight: 'semibold',
          color: '#374151',
          marginBottom: '20px'
        }}>
          👁️ Podgląd zmian
        </h2>
        
        <div style={{
          border: '2px solid #e5e7eb',
          borderRadius: '12px',
          padding: '20px',
          backgroundColor: '#f9fafb'
        }}>
          <h3 style={{
            fontSize: '1.25rem',
            fontWeight: 'bold',
            color: '#1f2937',
            marginBottom: '10px'
          }}>
            {formData.name || 'Nazwa projektu'}
          </h3>
          <p style={{
            color: '#6b7280',
            marginBottom: '15px',
            lineHeight: '1.5'
          }}>
            {formData.description || 'Opis projektu'}
          </p>
          <div style={{
            display: 'flex',
            flexWrap: 'wrap',
            gap: '15px',
            alignItems: 'center'
          }}>
            <span style={{
              padding: '4px 12px',
              backgroundColor: '#dbeafe',
              color: '#1e40af',
              borderRadius: '20px',
              fontSize: '0.875rem'
            }}>
              🏷️ {formData.category || 'Kategoria'}
            </span>
            <span style={{
              padding: '4px 12px',
              backgroundColor: 
                formData.status === 'active' ? '#dcfce7' : 
                formData.status === 'completed' ? '#e0e7ff' : '#fef3c7',
              color: 
                formData.status === 'active' ? '#166534' : 
                formData.status === 'completed' ? '#3730a3' : '#92400e',
              borderRadius: '20px',
              fontSize: '0.875rem'
            }}>
              📊 {
                formData.status === 'active' ? 'Aktywny' : 
                formData.status === 'completed' ? 'Zakończony' : 'Wstrzymany'
              }
            </span>
            <span style={{
              color: '#6b7280',
              fontSize: '0.875rem'
            }}>
              👤 {project?.owner?.name || 'Właściciel projektu'}
            </span>
            <span style={{
              color: '#6b7280',
              fontSize: '0.875rem'
            }}>
              📅 {project?.createdAt ? new Date(project.createdAt).toLocaleDateString('pl-PL') : 'Data utworzenia'}
            </span>
          </div>
        </div>
      </div>

      {/* Project Info */}
      {project && (
        <div style={{
          backgroundColor: '#f8fafc',
          padding: '20px',
          borderRadius: '8px',
          border: '1px solid #e2e8f0'
        }}>
          <h3 style={{
            fontSize: '1rem',
            fontWeight: 'medium',
            color: '#475569',
            marginBottom: '10px'
          }}>
            ℹ️ Informacje o projekcie
          </h3>
          <div style={{
            display: 'grid',
            gridTemplateColumns: 'repeat(auto-fit, minmax(200px, 1fr))',
            gap: '15px',
            fontSize: '0.875rem',
            color: '#64748b'
          }}>
            <div>
              <strong>Utworzony:</strong> {new Date(project.createdAt).toLocaleDateString('pl-PL')}
            </div>
            <div>
              <strong>Ostatnia aktualizacja:</strong> {new Date(project.updatedAt).toLocaleDateString('pl-PL')}
            </div>
            <div>
              <strong>Właściciel:</strong> {project.owner?.name || 'Nieznany'}
            </div>
            <div>
              <strong>ID projektu:</strong> {project._id}
            </div>
          </div>
        </div>
      )}
    </div>
  );
};

export default ProjectEdit;
