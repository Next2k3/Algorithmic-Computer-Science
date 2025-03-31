import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import numpy as np

# Load the MNIST dataset
(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()


# Normalize pixel values to be between 0 and 1
x_train = x_train / 255.0

# Reshape images to include channel dimension
x_train = x_train.reshape((x_train.shape[0], 28, 28, 1))


# Ścieżka do folderu z Twoimi danymi testowymi
custom_test_dir = "data"

# Wczytanie danych testowych
custom_test_dataset = keras.preprocessing.image_dataset_from_directory(
    custom_test_dir,
    image_size=(28, 28), 
    batch_size=32,  
    color_mode="grayscale",  
    shuffle=False  
)

# Normalizacja danych (taka sama jak w przykładzie)
def preprocess(image, label):
    image = image / 255.0  # Normalizacja pikseli do [0,1]
    return 1-image, label

custom_test_dataset = custom_test_dataset.map(preprocess)


# Konwersja danych do tablic NumPy (x_test i y_test)
x_test = np.concatenate([x for x, y in custom_test_dataset], axis=0)
y_test = np.concatenate([y for x, y in custom_test_dataset], axis=0)


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

# Znalezienie błędnych klasyfikacji
incorrect_indices = np.where(y_pred != y_test)[0]

# Tworzenie słownika {prawdziwa_liczba: [(zła_predykcja, indeks), ...]}
misclassified = {}

for idx in incorrect_indices:
    true_label = y_test[idx]
    predicted_label = y_pred[idx]
    
    if true_label not in misclassified:
        misclassified[true_label] = []
    
    misclassified[true_label].append((predicted_label, idx))

# Wyświetlenie błędnych klasyfikacji
print("Błędne klasyfikacje:")
for true_label, errors in misclassified.items():
    print(f"\nCyfra {true_label} została źle rozpoznana {len(errors)} razy:")
    for predicted_label, idx in errors[:5]:  # Wyświetl maksymalnie 5 przykładów dla każdej cyfry
        print(f"  → Rozpoznano jako {predicted_label} (indeks: {idx})")
