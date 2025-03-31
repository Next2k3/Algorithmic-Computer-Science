import tensorflow as tf
import tensorflow_decision_forests as tfdf
import pandas as pd
import numpy as np
from sklearn.metrics import accuracy_score, precision_score, recall_score

# Załadowanie danych MNIST
mnist = tf.keras.datasets.mnist
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# Spłaszczenie obrazów 28x28 do wektora 784-elementowego
x_train = x_train.reshape(len(x_train), -1).astype(np.float32)
x_test = x_test.reshape(len(x_test), -1).astype(np.float32)

# Konwersja do DataFrame z poprawionymi nazwami kolumn
train_df = pd.DataFrame(x_train, columns=[str(i) for i in range(x_train.shape[1])])
train_df["label"] = y_train.astype(str)  # Konwersja etykiet na stringi

test_df = pd.DataFrame(x_test, columns=[str(i) for i in range(x_test.shape[1])])
test_df["label"] = y_test.astype(str)

# Konwersja do datasetu TensorFlow
train_ds = tfdf.keras.pd_dataframe_to_tf_dataset(train_df, label="label")
test_ds = tfdf.keras.pd_dataframe_to_tf_dataset(test_df, label="label")

# Tworzenie i trenowanie modelu Random Forest
model = tfdf.keras.RandomForestModel(task=tfdf.keras.Task.CLASSIFICATION)
model.fit(train_ds)

# Predykcje na zbiorze testowym
y_pred = np.argmax(model.predict(test_ds), axis=1)

# Obliczenie metryk
accuracy = accuracy_score(y_test, y_pred)
precision = precision_score(y_test, y_pred, average="macro")
recall = recall_score(y_test, y_pred, average="macro")

print(f"Dokładność: {accuracy:.4f}")
print(f"Precyzja: {precision:.4f}")
print(f"Czułość: {recall:.4f}")
