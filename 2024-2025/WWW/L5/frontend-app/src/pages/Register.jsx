import React, { useState } from 'react';
import { Link, useNavigate } from 'react-router-dom';

const Register = () => {
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    password: '',
    confirmPassword: ''
  });
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState('');
  const [success, setSuccess] = useState('');
  const navigate = useNavigate();

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
    
    // Wyczyść błędy przy zmianie danych
    if (error) setError('');
  };

  const validateForm = () => {
    if (!formData.name.trim()) {
      setError('Nazwa użytkownika jest wymagana');
      return false;
    }

    if (!formData.email.trim()) {
      setError('Email jest wymagany');
      return false;
    }

    if (!formData.email.includes('@')) {
      setError('Wprowadź prawidłowy adres email');
      return false;
    }

    if (formData.password.length < 6) {
      setError('Hasło musi mieć co najmniej 6 znaków');
      return false;
    }

    if (formData.password !== formData.confirmPassword) {
      setError('Hasła nie są identyczne');
      return false;
    }

    return true;
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setError('');
    setSuccess('');

    if (!validateForm()) {
      return;
    }

    setLoading(true);

    try {
      const response = await fetch('/api/auth/register', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
          name: formData.name,
          email: formData.email,
          password: formData.password
        })
      });

      const data = await response.json();

      if (response.ok) {
        setSuccess('Konto zostało utworzone pomyślnie!');
        
        // Automatyczne logowanie po rejestracji
        localStorage.setItem('token', data.token);
        localStorage.setItem('user', JSON.stringify(data.user));
        
        // Przekieruj na dashboard po krótkim opóźnieniu
        setTimeout(() => {
          navigate('/dashboard');
        }, 1500);
      } else {
        setError(data.error || 'Błąd podczas rejestracji');
      }
    } catch (error) {
      console.error('Registration error:', error);
      setError('Błąd połączenia z serwerem');
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="auth-page">
      <div className="auth-container">
        <div className="auth-card">
          <div className="auth-header">
            <h1 className="auth-title">✨ Rejestracja</h1>
            <p className="auth-subtitle">
              Stwórz nowe konto i zacznij zarządzać swoimi projektami
            </p>
          </div>

          {error && (
            <div className="error-message">
              ⚠️ {error}
            </div>
          )}

          {success && (
            <div className="success-message">
              ✅ {success}
            </div>
          )}

          <form onSubmit={handleSubmit} className="auth-form">
            <div className="form-group">
              <label className="form-label">👤 Nazwa użytkownika</label>
              <input
                type="text"
                name="name"
                className="form-input"
                placeholder="Wprowadź swoją nazwę"
                value={formData.name}
                onChange={handleChange}
                required
                disabled={loading}
              />
            </div>

            <div className="form-group">
              <label className="form-label">📧 Email</label>
              <input
                type="email"
                name="email"
                className="form-input"
                placeholder="Wprowadź swój email"
                value={formData.email}
                onChange={handleChange}
                required
                disabled={loading}
              />
            </div>

            <div className="form-group">
              <label className="form-label">🔒 Hasło</label>
              <input
                type="password"
                name="password"
                className="form-input"
                placeholder="Wprowadź hasło (min. 6 znaków)"
                value={formData.password}
                onChange={handleChange}
                required
                disabled={loading}
                minLength="6"
              />
            </div>

            <div className="form-group">
              <label className="form-label">🔐 Potwierdź hasło</label>
              <input
                type="password"
                name="confirmPassword"
                className="form-input"
                placeholder="Powtórz hasło"
                value={formData.confirmPassword}
                onChange={handleChange}
                required
                disabled={loading}
              />
            </div>

            <button
              type="submit"
              className="btn btn-primary btn-full"
              disabled={loading}
            >
              {loading ? (
                <>
                  <span className="loading-spinner">⏳</span>
                  Tworzenie konta...
                </>
              ) : (
                <>
                  🚀 Utwórz konto
                </>
              )}
            </button>
          </form>

          <div className="auth-footer">
            <p className="auth-link-text">
              Masz już konto?{' '}
              <Link to="/login" className="auth-link">
                Zaloguj się
              </Link>
            </p>
          </div>
        </div>

        <div className="auth-features">
          <h3 className="features-title">🎯 Co możesz robić po rejestracji?</h3>
          <div className="features-list">
            <div className="feature-item">
              <div className="feature-icon">➕</div>
              <div className="feature-content">
                <h4>Twórz projekty</h4>
                <p>Dodawaj nowe projekty i organizuj swoją pracę</p>
              </div>
            </div>
            <div className="feature-item">
              <div className="feature-icon">🏷️</div>
              <div className="feature-content">
                <h4>Kategoryzuj</h4>
                <p>Sortuj projekty według kategorii i statusu</p>
              </div>
            </div>
            <div className="feature-item">
              <div className="feature-icon">👥</div>
              <div className="feature-content">
                <h4>Współpracuj</h4>
                <p>Dziel się projektami i komentuj z zespołem</p>
              </div>
            </div>
            <div className="feature-item">
              <div className="feature-icon">📊</div>
              <div className="feature-content">
                <h4>Analizuj</h4>
                <p>Śledź postępy i statystyki swoich projektów</p>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Register;
