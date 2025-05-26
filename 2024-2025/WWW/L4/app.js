const express = require('express');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const mongoose = require('mongoose');

const app = express();
app.use(express.json());

// JWT Secret
const JWT_SECRET = process.env.JWT_SECRET || 'your-super-secret-jwt-key';

// MongoDB connection
mongoose.connect(process.env.MONGODB_URI || 'mongodb://localhost:27017/rest_api_db')
  .then(() => console.log('MongoDB connected'))
  .catch(err => console.log('MongoDB connection error:', err));

// User Schema
const userSchema = new mongoose.Schema({
    name: { type: String, required: true },
    email: { type: String, required: true, unique: true },
    password: { type: String, required: true },
    role: { type: String, enum: ['user', 'admin'], default: 'user' },
    createdAt: { type: Date, default: Date.now }
});

// Project Schema
const projectSchema = new mongoose.Schema({
    name: { type: String, required: true },
    description: { type: String },
    category: { type: String, required: true },
    owner: { type: mongoose.Schema.Types.ObjectId, ref: 'User', required: true },
    status: { type: String, enum: ['active', 'completed', 'on-hold'], default: 'active' },
    createdAt: { type: Date, default: Date.now }
});

// Comment Schema
const commentSchema = new mongoose.Schema({
    text: { type: String, required: true },
    author: { type: mongoose.Schema.Types.ObjectId, ref: 'User', required: true },
    project: { type: mongoose.Schema.Types.ObjectId, ref: 'Project', required: true },
    createdAt: { type: Date, default: Date.now }
});

const User = mongoose.model('User', userSchema);
const Project = mongoose.model('Project', projectSchema);
const Comment = mongoose.model('Comment', commentSchema);

// Middleware for authentication
const authenticateToken = (req, res, next) => {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];

    if (!token) {
        return res.status(401).json({ error: 'Access token required' });
    }

    jwt.verify(token, JWT_SECRET, (err, user) => {
        if (err) {
            return res.status(403).json({ error: 'Invalid or expired token' });
        }
        req.user = user;
        next();
    });
};

// Middleware for admin authorization
const requireAdmin = (req, res, next) => {
    if (req.user.role !== 'admin') {
        return res.status(403).json({ error: 'Admin access required' });
    }
    next();
};

/* === TEST ROUTE === */
app.get('/api/test', (req, res) => {
    res.json({ message: 'API is working!', timestamp: new Date() });
});

/* === AUTHENTICATION === */
app.post('/api/auth/register', async (req, res) => {
    try {
        const { name, email, password, role } = req.body;
        
        if (!name || !email || !password) {
            return res.status(400).json({ error: 'Name, email and password are required' });
        }
        
        const hashedPassword = await bcrypt.hash(password, 10);
        
        const user = new User({
            name,
            email,
            password: hashedPassword,
            role: role || 'user'
        });
        
        await user.save();
        
        const token = jwt.sign(
            { id: user._id, email: user.email, role: user.role },
            JWT_SECRET,
            { algorithm: 'HS512', expiresIn: '24h' }
        );
        
        res.status(201).json({
            message: 'User created successfully',
            token,
            user: {
                id: user._id,
                name: user.name,
                email: user.email,
                role: user.role
            }
        });
    } catch (error) {
        if (error.code === 11000) {
            return res.status(409).json({ error: 'User with this email already exists' });
        }
        res.status(500).json({ error: 'Registration failed', details: error.message });
    }
});

app.post('/api/auth/login', async (req, res) => {
    try {
        const { email, password } = req.body;
        
        if (!email || !password) {
            return res.status(400).json({ error: 'Email and password are required' });
        }
        
        const user = await User.findOne({ email });
        if (!user) {
            return res.status(401).json({ error: 'Invalid credentials' });
        }
        
        const isValidPassword = await bcrypt.compare(password, user.password);
        if (!isValidPassword) {
            return res.status(401).json({ error: 'Invalid credentials' });
        }
        
        const token = jwt.sign(
            { id: user._id, email: user.email, role: user.role },
            JWT_SECRET,
            { algorithm: 'HS512',expiresIn: '24h' }
        );
        
        res.json({
            message: 'Login successful',
            token,
            user: {
                id: user._id,
                name: user.name,
                email: user.email,
                role: user.role
            }
        });
    } catch (error) {
        res.status(500).json({ error: 'Login failed', details: error.message });
    }
});

/* === USERS === */
app.get('/api/users', authenticateToken, requireAdmin, async (req, res) => {
    try {
        const users = await User.find({}, '-password');
        res.json(users);
    } catch (error) {
        res.status(500).json({ error: 'Failed to fetch users' });
    }
});

app.get('/api/users/:id', authenticateToken, async (req, res) => {
    try {
        const userId = req.params.id;
        
        // Validate ObjectId
        if (!mongoose.Types.ObjectId.isValid(userId)) {
            return res.status(400).json({ error: 'Invalid user ID format' });
        }
        
        // Users can only view their own profile, admins can view any profile
        if (req.user.role !== 'admin' && req.user.id !== userId) {
            return res.status(403).json({ error: 'Access denied' });
        }
        
        const user = await User.findById(userId, '-password');
        if (!user) {
            return res.status(404).json({ error: 'User not found' });
        }
        
        res.json(user);
    } catch (error) {
        res.status(500).json({ error: 'Failed to fetch user' });
    }
});

app.put('/api/users/:id', authenticateToken, async (req, res) => {
    try {
        const userId = req.params.id;
        
        // Validate ObjectId
        if (!mongoose.Types.ObjectId.isValid(userId)) {
            return res.status(400).json({ error: 'Invalid user ID format' });
        }
        
        // Users can only update their own profile, admins can update any profile
        if (req.user.role !== 'admin' && req.user.id !== userId) {
            return res.status(403).json({ error: 'Access denied' });
        }
        
        const { name, email, role } = req.body;
        const updateData = { name, email };
        
        // Only admins can change roles
        if (role && req.user.role === 'admin') {
            updateData.role = role;
        }
        
        const user = await User.findByIdAndUpdate(
            userId,
            updateData,
            { new: true, runValidators: true }
        ).select('-password');
        
        if (!user) {
            return res.status(404).json({ error: 'User not found' });
        }
        
        res.json(user);
    } catch (error) {
        res.status(500).json({ error: 'Failed to update user' });
    }
});

app.delete('/api/users/:id', authenticateToken, requireAdmin, async (req, res) => {
    try {
        const userId = req.params.id;
        
        // Validate ObjectId
        if (!mongoose.Types.ObjectId.isValid(userId)) {
            return res.status(400).json({ error: 'Invalid user ID format' });
        }
        
        const user = await User.findByIdAndDelete(userId);
        if (!user) {
            return res.status(404).json({ error: 'User not found' });
        }
        
        res.status(204).send();
    } catch (error) {
        res.status(500).json({ error: 'Failed to delete user' });
    }
});

/* === PROJECTS === */
app.get('/api/projects', async (req, res) => {
    try {
        const { 
            page = 1, 
            limit = 10, 
            sortBy = 'createdAt', 
            sortOrder = 'desc',
            category, 
            status,
            owner 
        } = req.query;

        const query = {};
        
        if (category) query.category = category;
        if (status) query.status = status;
        if (owner) {
            if (!mongoose.Types.ObjectId.isValid(owner)) {
                return res.status(400).json({ error: 'Invalid owner ID format' });
            }
            query.owner = owner;
        }

        const sortOptions = {};
        sortOptions[sortBy] = sortOrder === 'desc' ? -1 : 1;

        const skip = (page - 1) * limit;
        
        const projects = await Project.find(query)
            .populate('owner', 'name email')
            .sort(sortOptions)
            .skip(skip)
            .limit(Number(limit));

        const total = await Project.countDocuments(query);

        res.json({
            page: Number(page),
            limit: Number(limit),
            total,
            totalPages: Math.ceil(total / limit),
            results: projects
        });
    } catch (error) {
        res.status(500).json({ error: 'Failed to fetch projects', details: error.message });
    }
});

app.get('/api/projects/:id', async (req, res) => {
    try {
        const projectId = req.params.id;
        
        // Validate ObjectId
        if (!mongoose.Types.ObjectId.isValid(projectId)) {
            return res.status(400).json({ error: 'Invalid project ID format' });
        }
        
        const project = await Project.findById(projectId)
            .populate('owner', 'name email');
        
        if (!project) {
            return res.status(404).json({ error: 'Project not found' });
        }
        
        res.json(project);
    } catch (error) {
        res.status(500).json({ error: 'Failed to fetch project' });
    }
});

app.post('/api/projects', authenticateToken, async (req, res) => {
    try {
        const { name, description, category, status } = req.body;
        
        if (!name || !category) {
            return res.status(400).json({ error: 'Name and category are required' });
        }
        
        const project = new Project({
            name,
            description,
            category,
            status: status || 'active',
            owner: req.user.id
        });
        
        await project.save();
        await project.populate('owner', 'name email');
        
        res.status(201).json(project);
    } catch (error) {
        res.status(500).json({ error: 'Failed to create project', details: error.message });
    }
});

app.put('/api/projects/:id', authenticateToken, async (req, res) => {
    try {
        const projectId = req.params.id;
        
        // Validate ObjectId
        if (!mongoose.Types.ObjectId.isValid(projectId)) {
            return res.status(400).json({ error: 'Invalid project ID format' });
        }
        
        const project = await Project.findById(projectId);
        
        if (!project) {
            return res.status(404).json({ error: 'Project not found' });
        }
        
        // Only project owner or admin can update
        if (project.owner.toString() !== req.user.id && req.user.role !== 'admin') {
            return res.status(403).json({ error: 'Access denied' });
        }
        
        const { name, description, category, status } = req.body;
        
        const updatedProject = await Project.findByIdAndUpdate(
            projectId,
            { name, description, category, status },
            { new: true, runValidators: true }
        ).populate('owner', 'name email');
        
        res.json(updatedProject);
    } catch (error) {
        res.status(500).json({ error: 'Failed to update project' });
    }
});

app.delete('/api/projects/:id', authenticateToken, async (req, res) => {
    try {
        const projectId = req.params.id;
        
        // Validate ObjectId
        if (!mongoose.Types.ObjectId.isValid(projectId)) {
            return res.status(400).json({ error: 'Invalid project ID format' });
        }
        
        const project = await Project.findById(projectId);
        
        if (!project) {
            return res.status(404).json({ error: 'Project not found' });
        }
        
        // Only project owner or admin can delete
        if (project.owner.toString() !== req.user.id && req.user.role !== 'admin') {
            return res.status(403).json({ error: 'Access denied' });
        }
        
        await Project.findByIdAndDelete(projectId);
        await Comment.deleteMany({ project: projectId }); // Delete associated comments
        
        res.status(204).send();
    } catch (error) {
        res.status(500).json({ error: 'Failed to delete project' });
    }
});

/* === COMMENTS === */
app.get('/api/projects/:projectId/comments', async (req, res) => {
    try {
        const projectId = req.params.projectId;
        const { page = 1, limit = 20, sortBy = 'createdAt', sortOrder = 'desc' } = req.query;
        
        // Validate projectId format
        if (!mongoose.Types.ObjectId.isValid(projectId)) {
            return res.status(400).json({ error: 'Invalid project ID format' });
        }
        
        const sortOptions = {};
        sortOptions[sortBy] = sortOrder === 'desc' ? -1 : 1;
        
        const skip = (page - 1) * limit;
        
        const comments = await Comment.find({ project: projectId })
            .populate('author', 'name email')
            .sort(sortOptions)
            .skip(skip)
            .limit(Number(limit));
        
        const total = await Comment.countDocuments({ project: projectId });
        
        res.json({
            page: Number(page),
            limit: Number(limit),
            total,
            totalPages: Math.ceil(total / limit),
            results: comments
        });
    } catch (error) {
        res.status(500).json({ error: 'Failed to fetch comments', details: error.message });
    }
});

app.post('/api/projects/:projectId/comments', authenticateToken, async (req, res) => {
    try {
        const projectId = req.params.projectId;
        const { text } = req.body;
        
        // Validate projectId format
        if (!mongoose.Types.ObjectId.isValid(projectId)) {
            return res.status(400).json({ error: 'Invalid project ID format' });
        }
        
        if (!text) {
            return res.status(400).json({ error: 'Comment text is required' });
        }
        
        // Check if project exists
        const project = await Project.findById(projectId);
        if (!project) {
            return res.status(404).json({ error: 'Project not found' });
        }
        
        const comment = new Comment({
            text,
            author: req.user.id,
            project: projectId
        });
        
        await comment.save();
        await comment.populate('author', 'name email');
        
        res.status(201).json(comment);
    } catch (error) {
        res.status(500).json({ error: 'Failed to create comment', details: error.message });
    }
});

app.put('/api/projects/:projectId/comments/:commentId', authenticateToken, async (req, res) => {
    try {
        const { commentId } = req.params;
        
        // Validate ID formats
        if (!mongoose.Types.ObjectId.isValid(commentId)) {
            return res.status(400).json({ error: 'Invalid comment ID format' });
        }
        
        const comment = await Comment.findById(commentId);
        
        if (!comment) {
            return res.status(404).json({ error: 'Comment not found' });
        }
        
        // Only comment author or admin can update
        if (comment.author.toString() !== req.user.id && req.user.role !== 'admin') {
            return res.status(403).json({ error: 'Access denied' });
        }
        
        const { text } = req.body;
        
        if (!text) {
            return res.status(400).json({ error: 'Comment text is required' });
        }
        
        const updatedComment = await Comment.findByIdAndUpdate(
            commentId,
            { text },
            { new: true, runValidators: true }
        ).populate('author', 'name email');
        
        res.json(updatedComment);
    } catch (error) {
        res.status(500).json({ error: 'Failed to update comment' });
    }
});

app.delete('/api/projects/:projectId/comments/:commentId', authenticateToken, async (req, res) => {
    try {
        const { projectId, commentId } = req.params;
        
        // Validate ID formats
        if (!mongoose.Types.ObjectId.isValid(projectId) || !mongoose.Types.ObjectId.isValid(commentId)) {
            return res.status(400).json({ error: 'Invalid ID format' });
        }
        
        const comment = await Comment.findById(commentId);
        
        if (!comment) {
            return res.status(404).json({ error: 'Comment not found' });
        }
        
        // Only comment author, project owner, or admin can delete
        const project = await Project.findById(projectId);
        if (comment.author.toString() !== req.user.id && 
            project && project.owner.toString() !== req.user.id && 
            req.user.role !== 'admin') {
            return res.status(403).json({ error: 'Access denied' });
        }
        
        await Comment.findByIdAndDelete(commentId);
        
        res.status(204).send();
    } catch (error) {
        res.status(500).json({ error: 'Failed to delete comment' });
    }
});

// 404 handler
app.use('*', (req, res) => {
    res.status(404).json({ error: 'Endpoint not found' });
});

// Error handling middleware
app.use((err, req, res, next) => {
    console.error(err.stack);
    
    if (err.name === 'ValidationError') {
        return res.status(400).json({ error: err.message });
    }
    
    if (err.name === 'CastError') {
        return res.status(400).json({ error: 'Invalid ID format' });
    }
    
    if (err.code === 11000) {
        return res.status(409).json({ error: 'Resource already exists' });
    }
    
    res.status(500).json({ error: 'Internal server error' });
});

/* === SERVER === */
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
