import api from './api';

export const commentService = {
  // GET - pobieranie komentarzy dla projektu
  getComments: async (projectId, params = {}) => {
    try {
      const response = await api.get(`/projects/${projectId}/comments`, { params });
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to fetch comments' 
      };
    }
  },

  // POST - dodawanie komentarza
  createComment: async (projectId, commentData) => {
    try {
      const response = await api.post(`/projects/${projectId}/comments`, commentData);
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to create comment' 
      };
    }
  },

  // PUT - aktualizacja komentarza
  updateComment: async (projectId, commentId, commentData) => {
    try {
      const response = await api.put(`/projects/${projectId}/comments/${commentId}`, commentData);
      return { success: true, data: response.data };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to update comment' 
      };
    }
  },

  // DELETE - usuwanie komentarza
  deleteComment: async (projectId, commentId) => {
    try {
      await api.delete(`/projects/${projectId}/comments/${commentId}`);
      return { success: true };
    } catch (error) {
      return { 
        success: false, 
        error: error.response?.data?.error || 'Failed to delete comment' 
      };
    }
  }
};