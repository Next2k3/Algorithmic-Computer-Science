import React, { useState, useEffect } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { useAuth } from '../context/AuthContext';

const Login = () => {
  const [formData, setFormData] = useState({
    email: '',
    password: ''
  });
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState('');
  
  const navigate = useNavigate();
  const { login, user } = useAuth();

  // Przekieruj zalogowanego użytkownika do dashboard
  useEffect(() => {
    if (user) {
      navigate('/dashboard');
    }
  }, [user, navigate]);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
    
    // Wyczyść błąd przy wprowadzaniu danych
    if (error) {
      setError('');
    }
  };

  const validateForm = () => {
    if (!formData.email || !formData.password) {
      setError('Wszystkie pola są wymagane');
      return false;
    }
    
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!emailRegex.test(formData.email)) {
      setError('Wprowadź poprawny adres email');
      return false;
    }
    
    return true;
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    
    if (!validateForm()) {
      return;
    }
    
    setLoading(true);
    setError('');

    try {
      const result = await login(formData.email, formData.password);
      
      if (result.success) {
        // Przekierowanie nastąpi automatycznie przez useEffect
        console.log('Logowanie pomyślne');
      } else {
        setError(result.error || 'Nieprawidłowy email lub hasło');
      }
    } catch (error) {
      console.error('Login error:', error);
      setError('Błąd połączenia z serwerem. Spróbuj ponownie.');
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="auth-page">
      <div className="auth-container">
        <div className="auth-card">
          {/* Header */}
          <div className="auth-header">
            <h1 className="page-title">
              🔐 Zaloguj się
            </h1>
            <p className="auth-subtitle">
              Uzyskaj dostęp do swojego pulpitu i projektów
            </p>
          </div>

          {/* Error Message */}
          {error && (
            <div className="error-message">
              <span className="error-icon">⚠️</span>
              <span className="error-text">{error}</span>
            </div>
          )}

          {/* Login Form */}
          <form onSubmit={handleSubmit} className="auth-form">
            <div className="form-group">
              <label htmlFor="email" className="form-label">
                📧 Adres email
              </label>
              <input
                id="email"
                type="email"
                name="email"
                className="form-input"
                placeholder="np. jan.kowalski@email.com"
                value={formData.email}
                onChange={handleChange}
                required
                disabled={loading}
                autoComplete="email"
              />
            </div>

            <div className="form-group">
              <label htmlFor="password" className="form-label">
                🔒 Hasło
              </label>
              <input
                id="password"
                type="password"
                name="password"
                className="form-input"
                placeholder="Wprowadź swoje hasło"
                value={formData.password}
                onChange={handleChange}
                required
                disabled={loading}
                autoComplete="current-password"
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
                  Logowanie...
                </>
              ) : (
                <>
                  🚀 Zaloguj się
                </>
              )}
            </button>
          </form>

          {/* Footer */}
          <div className="auth-footer">
            <div className="auth-divider">
              <span>lub</span>
            </div>
            
            <p className="auth-link-text">
              Nie masz jeszcze konta?{' '}
              <Link to="/register" className="auth-link">
                Zarejestruj się tutaj
              </Link>
            </p>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Login;
