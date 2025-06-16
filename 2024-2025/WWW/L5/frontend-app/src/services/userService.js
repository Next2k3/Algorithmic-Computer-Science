import api from './api';

export const userService = {
  // GET - pobieranie wszystkich użytkowników (tylko admin)
  getUsers: async () => {
    try {
      const response = await api.get('/users');
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to fetch users' 
      };
    }
  },

  // GET - pobieranie pojedynczego użytkownika
  getUser: async (id) => {
    try {
      const response = await api.get(`/users/${id}`);
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to fetch user' 
      };
    }
  },

  // PUT - aktualizacja użytkownika
  updateUser: async (id, userData) => {
    try {
      const response = await api.put(`/users/${id}`, userData);
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to update user' 
      };
    }
  },

  // DELETE - usuwanie użytkownika (tylko admin)
  deleteUser: async (id) => {
    try {
      await api.delete(`/users/${id}`);
      return { success: true };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to delete user' 
      };
    }
  }
};
