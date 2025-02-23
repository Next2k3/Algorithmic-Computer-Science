Autor: Paweł Krzyszczak, 272379

# Opis projektu

## Struktura plików
- **`Graph.cpp`**  
  Zawiera implementację grafu, wczytywanie danych z pliku oraz zapis wyników do pliku.
  
- **`Dijkstra.cpp`**  
  Implementacja algorytmu Dijkstry do wyznaczania najkrótszej ścieżki w grafie. Zawiera również funkcję `main` umożliwiającą uruchomienie programu.
  
- **`Dial.cpp`**  
  Implementacja algorytmu Diala do wyszukiwania najkrótszej ścieżki w grafie. Plik zawiera funkcję `main` do uruchomienia programu.
  
- **`RadixHeap.cpp`**  
  Implementacja algorytmu Radix Heap do wyznaczania najkrótszej ścieżki w grafie. Zawiera funkcję `main` umożliwiającą uruchomienie programu.

---

## Kompilacja
Do kompilacji projektu należy użyć polecenia:  
make

## Uruchomienie programu

Jeśli chcemy wyznaczyć czas wyznaczania najkrótszej ścieżki
- ./dijkstra -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res
- ./dial -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res
- ./RadixHeap -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res

Jeśli chcemy wyznaczyć długość najkrótszej ścieżki między podanymi parami wierzchołków
- ./dijkstra -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res,
- ./dial -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res,
- ./RadixHeap -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res.


