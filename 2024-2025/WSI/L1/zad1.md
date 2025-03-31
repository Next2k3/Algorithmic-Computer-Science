# Sprawozdanie - Zadanie 1: Sieć Neuronowa do Rozpoznawania Cyfr

## Opis Modelu
- Użyto sieci neuronowej konwolucyjnej (CNN) z biblioteki Keras/TensorFlow
- Architektura modelu składa się z:
  - 3 warstw konwolucyjnych z aktywacją ReLU
  - 2 warstw MaxPooling
  - Warstwy Flatten
  - 2 warstw Dense (w tym warstwa wyjściowa z aktywacją softmax)

## Wyniki Treningu
- Zbiór treningowy: MNIST
- Liczba epok: 5
- Optymalizator: Adam
- Funkcja straty: sparse categorical crossentropy

## Metryki Oceny
- Dokładność na zbiorze testowym: 99.xx%
- Precyzja: 99.xx%

## Wnioski
Model sieci neuronowej charakteryzuje się bardzo wysoką skutecznością rozpoznawania cyfr, osiągając niemal 100% dokładności na standardowym zbiorze MNIST.
