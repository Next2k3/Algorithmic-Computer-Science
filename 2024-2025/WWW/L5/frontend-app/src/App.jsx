import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import { AuthProvider, useAuth } from './context/AuthContext';
import Navigation from './components/Layout/Navigation'; 
import Login from './pages/Login';
import Register from './pages/Register';
import Dashboard from './pages/Dashboard';
import Projects from './pages/Projects';
import ProjectNew from './pages/ProjectNew';
import ProjectEdit from './pages/ProjectEdit';
import ProjectDetail from './pages/ProjectDetail';
import Users from './pages/Users';
import Profile from './pages/Profile';
import './styles.css'

// Protected Route Component
const ProtectedRoute = ({ children }) => {
  const { isAuthenticated, loading } = useAuth();
  
  if (loading) {
    return <div className="flex justify-center items-center h-screen">Loading...</div>;
  }
  
  return isAuthenticated ? children : <Navigate to="/login" />;
};

// Admin Only Route Component
const AdminRoute = ({ children }) => {
  const { isAdmin, loading } = useAuth();
  
  if (loading) {
    return <div className="flex justify-center items-center h-screen">Loading...</div>;
  }
  
  return isAdmin ? children : <Navigate to="/dashboard" />;
};

// Public Route Component (redirect if authenticated)
const PublicRoute = ({ children }) => {
  const { isAuthenticated, loading } = useAuth();
  
  if (loading) {
    return <div className="flex justify-center items-center h-screen">Loading...</div>;
  }
  
  return !isAuthenticated ? children : <Navigate to="/dashboard" />;
};

// Layout Component for authenticated users
const AuthenticatedLayout = ({ children }) => {
  return (
    <>
      <Navigation />
      <main className="main-content">
        {children}
      </main>
    </>
  );
};

function AppContent() {
  return (
    <Router>
      <Routes>
        {/* Public routes - bez nawigacji */}
        <Route path="/login" element={
          <PublicRoute>
            <Login />
          </PublicRoute>
        } />
        <Route path="/register" element={
          <PublicRoute>
            <Register />
          </PublicRoute>
        } />
        
        {/* Protected routes - z nawigacją */}
        <Route path="/" element={
          <ProtectedRoute>
            <AuthenticatedLayout>
              <Navigate to="/dashboard" />
            </AuthenticatedLayout>
          </ProtectedRoute>
        } />
        
        <Route path="/dashboard" element={
          <ProtectedRoute>
            <AuthenticatedLayout>
              <Dashboard />
            </AuthenticatedLayout>
          </ProtectedRoute>
        } />
        
        <Route path="/projects" element={
          <ProtectedRoute>
            <AuthenticatedLayout>
              <Projects />
            </AuthenticatedLayout>
          </ProtectedRoute>
        } />
        
        <Route path="/projects/new" element={
          <ProtectedRoute>
            <AuthenticatedLayout>
              <ProjectNew />
            </AuthenticatedLayout>
          </ProtectedRoute>
        } />
        
        <Route path="/projects/:id/edit" element={
	  <ProtectedRoute>
	    <AuthenticatedLayout>
	      <ProjectEdit />
	    </AuthenticatedLayout>
	  </ProtectedRoute>
	} />
        
        <Route path="/projects/:id" element={
          <ProtectedRoute>
            <AuthenticatedLayout>
              <ProjectDetail />
            </AuthenticatedLayout>
          </ProtectedRoute>
        } />
        
        <Route path="/profile" element={
          <ProtectedRoute>
            <AuthenticatedLayout>
              <Profile />
            </AuthenticatedLayout>
          </ProtectedRoute>
        } />
        
        {/* Admin only routes */}
        <Route path="/users" element={
          <AdminRoute>
            <AuthenticatedLayout>
              <Users />
            </AuthenticatedLayout>
          </AdminRoute>
        } />
        
        {/* Catch all route */}
        <Route path="*" element={<Navigate to="/" />} />
      </Routes>
    </Router>
  );
}

function App() {
  
  return (
    <AuthProvider>
      {<AppContent />}
    </AuthProvider>
  );
}

export default App;
