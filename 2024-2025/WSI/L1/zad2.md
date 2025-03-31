# Sprawozdanie - Zadanie 2: Własny Zbiór Testowy

## Przygotowanie Danych
- Wczytano własne próbki cyfr z folderu "data"
- Rozmiar obrazów: 28x28 pikseli
- Tryb: skala szarości
- Normalizacja pikseli do zakresu [0, 1]

## Wyniki Testu na Własnym Zbiorze
- Dokładność na własnym zbiorze testowym: zależy od jakości próbek
- Możliwe przyczyny błędów:
  1. Różnice w stylu pisma między próbkami treningowymi a własnymi
  2. Mniejsza liczba próbek własnych w porównaniu do zbioru MNIST
  3. Potencjalne różnice w preprocessing (np. kontrast, kształt cyfr)

## Wnioski
Dla dokładnej oceny modelu kluczowe jest:
- Zebranie reprezentatywnej próby własnych cyfr
- Zachowanie podobnego stylu pisma jak w zbiorze MNIST
- Porównanie wyników z oryginalnymi danymi treningowymi
