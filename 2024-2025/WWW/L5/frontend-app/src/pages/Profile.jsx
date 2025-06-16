import React, { useState, useEffect } from 'react';
import { useAuth } from '../context/AuthContext';
import { userService } from '../services/userService';

const Profile = () => {
  const { user, updateUser } = useAuth();
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    role: ''
  });
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState('');
  const [success, setSuccess] = useState('');

  useEffect(() => {
    if (user) {
      setFormData({
        name: user.name || '',
        email: user.email || '',
        role: user.role || ''
      });
    }
  }, [user]);

  const handleChange = (e) => { 
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };
  const handleSubmit = async (e) => {
    e.preventDefault();
    setError('');
    setSuccess('');
    setLoading(true);

    try {
      const result = await userService.updateUser(user.id, formData);
      console.log('Update result:', result);
      if (result.success) {
        setSuccess('Profil został pomyślnie zaktualizowany!');
      } else {
        setError(result.error);
      }
    } catch (err) {
      setError('Nie udało się zaktualizować profilu');
    } finally {
      setLoading(false);
    }
  };

  if (!user) {
    return (
      <div className="loading-container">
        <div className="spinner"></div>
        <div className="loading-text">Ładowanie profilu...</div>
        <p className="loading-subtext">Proszę poczekać, trwa weryfikacja Twojego konta...</p>
      </div>
    );
  }

  return (
    <div className="dashboard">
      {/* Header */}
      <div className="dashboard-header">
        <div className="header-content">
          <div>
            <h1 className="dashboard-title">
              Ustawienia Profilu 👤
            </h1>
            <p className="dashboard-subtitle">
              Zarządzaj swoimi danymi osobowymi
            </p>
          </div>
        </div>
      </div>

      <div className="main-content">
        {/* Profile Card */}
        <div className="card">
          <div className="card-header">
            <div>
              <h2 className="card-title">Informacje Osobowe</h2>
              <p className="card-subtitle">Zaktualizuj swoje dane użytkownika</p>
            </div>
          </div>

          <div style={{padding: '0 24px 24px 24px'}}>
            {/* Error Message */}
            {error && (
              <div className="error-message" style={{marginBottom: '24px'}}>
                <svg width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                  <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM8.707 7.293a1 1 0 00-1.414 1.414L8.586 10l-1.293 1.293a1 1 0 101.414 1.414L10 11.414l1.293 1.293a1 1 0 001.414-1.414L11.414 10l1.293-1.293a1 1 0 00-1.414-1.414L10 8.586 8.707 7.293z" clipRule="evenodd" />
                </svg>
                <span>{error}</span>
              </div>
            )}

            {/* Success Message */}
            {success && (
              <div className="success-message" style={{marginBottom: '24px'}}>
                <svg width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
                  <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z" clipRule="evenodd" />
                </svg>
                <span>{success}</span>
              </div>
            )}

            {/* Profile Form */}
            <form onSubmit={handleSubmit} className="profile-form">
              <div className="form-group">
                <label htmlFor="name" className="form-label">
                  <svg width="16" height="16" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                    <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M16 7a4 4 0 11-8 0 4 4 0 018 0zM12 14a7 7 0 00-7 7h14a7 7 0 00-7-7z" />
                  </svg>
                  Imię i Nazwisko
                </label>
                <input
                  type="text"
                  id="name"
                  name="name"
                  value={formData.name}
                  onChange={handleChange}
                  required
                  className="form-input"
                  placeholder="Wprowadź swoje imię i nazwisko"
                />
              </div>

              <div className="form-group">
                <label htmlFor="email" className="form-label">
                  <svg width="16" height="16" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                    <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M16 12a4 4 0 10-8 0 4 4 0 008 0zm0 0v1.5a2.5 2.5 0 005 0V9a9 9 0 10-9 9m4.5-1.206a8.959 8.959 0 01-4.5 1.207" />
                  </svg>
                  Adres E-mail
                </label>
                <input
                  type="email"
                  id="email"
                  name="email"
                  value={formData.email}
                  onChange={handleChange}
                  required
                  className="form-input"
                  placeholder="twoj@email.com"
                />
              </div>

              <div className="form-group">
                <label htmlFor="role" className="form-label">
                  <svg width="16" height="16" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                    <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 12l2 2 4-4m5.618-4.016A11.955 11.955 0 0112 2.944a11.955 11.955 0 01-8.618 3.04A12.02 12.02 0 003 9c0 5.591 3.824 10.29 9 11.622 5.176-1.332 9-6.03 9-11.622 0-1.042-.133-2.052-.382-3.016z" />
                  </svg>
                  Rola
                </label>
                <input
                  type="text"
                  id="role"
                  name="role"
                  value={formData.role}
                  disabled
                  className="form-input form-input-disabled"
                  placeholder="Rola użytkownika"
                />
                <p className="form-help-text">
                  Rola nie może być zmieniona. Skontaktuj się z administratorem w razie potrzeby.
                </p>
              </div>

              <div className="form-actions">
                <button
                  type="submit"
                  disabled={loading}
                  className="btn-primary btn-full"
                >
                  {loading ? (
                    <>
                      <div className="login-spinner"></div>
                      Aktualizowanie...
                    </>
                  ) : (
                    <>
                      <svg width="16" height="16" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                        <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M5 13l4 4L19 7" />
                      </svg>
                      Zaktualizuj Profil
                    </>
                  )}
                </button>
              </div>
            </form>
          </div>
        </div>

        {/* Account Information Card */}
        <div className="card">
          <div className="card-header">
            <div>
              <h2 className="card-title">Informacje o Koncie</h2>
              <p className="card-subtitle">Szczegóły Twojego konta użytkownika</p>
            </div>
          </div>
          
          <div style={{padding: '0 24px 24px 24px'}}>
            <div className="account-info-grid">
              <div className="account-info-item">
                <div className="account-info-header">
                  <svg width="20" height="20" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                    <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M7 7h.01M7 3h5c.512 0 1.024.195 1.414.586l7 7a2 2 0 010 2.828l-7 7a2 2 0 01-2.828 0l-7-7A1.994 1.994 0 013 12V7a4 4 0 014-4z" />
                  </svg>
                  <span className="account-info-label">ID Użytkownika</span>
                </div>
                <span className="account-info-value">{user.id}</span>
              </div>
              
              <div className="account-info-item">
                <div className="account-info-header">
                  <svg width="20" height="20" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                    <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M8 7V3a2 2 0 012-2h4a2 2 0 012 2v4m-6 4h6m-6 4h6m2 5H7a2 2 0 01-2-2V5a2 2 0 012-2h5.586a1 1 0 01.707.293l5.414 5.414a1 1 0 01.293.707V19a2 2 0 01-2 2z" />
                  </svg>
                  <span className="account-info-label">Data Utworzenia</span>
                </div>
                <span className="account-info-value">
                  {user.createdAt ? new Date(user.createdAt).toLocaleDateString('pl-PL') : 'Brak danych'}
                </span>
              </div>

              <div className="account-info-item">
                <div className="account-info-header">
                  <svg width="20" height="20" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                    <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 12l2 2 4-4m5.618-4.016A11.955 11.955 0 0112 2.944a11.955 11.955 0 01-8.618 3.04A12.02 12.02 0 003 9c0 5.591 3.824 10.29 9 11.622 5.176-1.332 9-6.03 9-11.622 0-1.042-.133-2.052-.382-3.016z" />
                  </svg>
                  <span className="account-info-label">Status Konta</span>
                </div>
                <span className="account-status-active">Aktywne</span>
              </div>
            </div>
          </div>
        </div>

      </div>
    </div>
  );
};

export default Profile;
