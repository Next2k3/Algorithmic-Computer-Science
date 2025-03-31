import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import numpy as np

# Load the MNIST dataset
(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()

# Normalize pixel values to be between 0 and 1
x_train, x_test = x_train / 255.0, x_test / 255.0

# Reshape images to include channel dimension
x_train = x_train.reshape((x_train.shape[0], 28, 28, 1))
x_test = x_test.reshape((x_test.shape[0], 28, 28, 1))

# Build the neural network model
model = keras.Sequential([
    layers.Conv2D(32, (3, 3), activation='relu', input_shape=(28, 28, 1)),
    layers.MaxPooling2D((2, 2)),
    layers.Conv2D(64, (3, 3), activation='relu'),
    layers.MaxPooling2D((2, 2)),
    layers.Conv2D(64, (3, 3), activation='relu'),
    layers.Flatten(),
    layers.Dense(64, activation='relu'),
    layers.Dense(10, activation='softmax')
])

# Compile the model
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# Train the model
history = model.fit(x_train, y_train, epochs=5, 
                    validation_data=(x_test, y_test))

# Evaluate the model
test_loss, test_accuracy = model.evaluate(x_test, y_test, verbose=2)

# Predict on test data
y_pred = np.argmax(model.predict(x_test), axis=1)

# Manual precision calculation
def calculate_precision(y_true, y_pred):
    classes = np.unique(y_true)
    precisions = []
    for cls in classes:
        # True Positives for this class
        tp = np.sum((y_true == cls) & (y_pred == cls))
        # All predictions for this class
        pred_cls = np.sum(y_pred == cls)
        # Precision = TP / (TP + FP)
        precision = tp / pred_cls if pred_cls > 0 else 0
        precisions.append(precision)
    
    # Weighted average precision
    class_weights = np.bincount(y_true) / len(y_true)
    weighted_precision = np.average(precisions, weights=class_weights)
    
    return weighted_precision

# Calculate precision
test_precision = calculate_precision(y_test, y_pred)

print(f"Test Accuracy: {test_accuracy * 100:.2f}%")
print(f"Test Precision: {test_precision * 100:.2f}%")
