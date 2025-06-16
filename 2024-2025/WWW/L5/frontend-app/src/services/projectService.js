import api from './api';

export const projectService = {
  // GET - pobieranie listy projektów
  getProjects: async (params = {}) => {
    try {
      const response = await api.get('/projects', { params });
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to fetch projects' 
      };
    }
  },

  // GET - pobieranie pojedynczego projektu
  getProject: async (id) => {
    try {
      const response = await api.get(`/projects/${id}`);
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to fetch project' 
      };
    }
  },

  // POST - tworzenie nowego projektu
  createProject: async (projectData) => {
    try {
      const response = await api.post('/projects', projectData);
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to create project' 
      };
    }
  },

  // PUT - aktualizacja projektu
  updateProject: async (id, projectData) => {
    try {
      const response = await api.put(`/projects/${id}`, projectData);
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to update project' 
      };
    }
  },

  // DELETE - usuwanie projektu
  deleteProject: async (id) => {
    try {
      await api.delete(`/projects/${id}`);
      return { success: true };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to delete project' 
      };
    }
  }
};