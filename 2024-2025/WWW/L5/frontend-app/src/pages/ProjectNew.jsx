import React, { useState } from 'react';

const NewProject = () => {
  const [formData, setFormData] = useState({
    name: '',
    description: '',
    category: '',
    status: 'active'
  });
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState('');

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
      const response = await fetch('/api/projects', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${token}`
        },
        body: JSON.stringify(formData)
      });

      const data = await response.json();

      if (response.ok) {
        // Redirect to projects page
        window.location.href = '/projects';
      } else {
        setError(data.error || 'Błąd podczas tworzenia projektu');
      }
    } catch (error) {
      console.error('Error creating project:', error);
      setError('Błąd połączenia z serwerem');
    } finally {
      setLoading(false);
    }
  };

  const handleCancel = () => {
    window.location.href = '/projects';
  };

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
        <h1 style={{ 
          fontSize: '2rem',
          fontWeight: 'bold',
          color: '#1f2937',
          margin: 0
        }}>
          ➕ Nowy projekt
        </h1>
        <button 
          onClick={handleCancel}
          style={{
            padding: '10px 20px',
            backgroundColor: '#6b7280',
            color: 'white',
            border: 'none',
            borderRadius: '8px',
            cursor: 'pointer'
          }}
        >
          ← Powrót do projektów
        </button>
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
              📊 Status początkowy
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
              disabled={loading || !formData.name || !formData.category}
              style={{
                padding: '12px 24px',
                backgroundColor: (!formData.name || !formData.category) ? '#9ca3af' : '#3b82f6',
                color: 'white',
                border: 'none',
                borderRadius: '8px',
                fontSize: '1rem',
                cursor: (loading || !formData.name || !formData.category) ? 'not-allowed' : 'pointer'
              }}
            >
              {loading ? '⏳ Tworzę...' : '✅ Utwórz projekt'}
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
        border: '1px solid #e5e7eb'
      }}>
        <h2 style={{ 
          fontSize: '1.5rem',
          fontWeight: 'semibold',
          color: '#374151',
          marginBottom: '20px'
        }}>
          👁️ Podgląd
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
              backgroundColor: formData.status === 'active' ? '#dcfce7' : '#fef3c7',
              color: formData.status === 'active' ? '#166534' : '#92400e',
              borderRadius: '20px',
              fontSize: '0.875rem'
            }}>
              📊 {formData.status === 'active' ? 'Aktywny' : 'Wstrzymany'}
            </span>
            <span style={{
              color: '#6b7280',
              fontSize: '0.875rem'
            }}>
              📅 {new Date().toLocaleDateString('pl-PL')}
            </span>
          </div>
        </div>
      </div>
    </div>
  );
};

export default NewProject;
