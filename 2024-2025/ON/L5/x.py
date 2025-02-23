import matplotlib.pyplot as plt
import os
import sys

# Funkcja do tworzenia wykresu z danych z wielu plików i zapisywania ich w folderze
def plot_and_save_from_files(filenames, output_folder):
    # Sprawdzamy, czy folder istnieje, jeśli nie, to go tworzymy
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    for filename in filenames:
        if not os.path.exists(filename):
            print(f"Plik {filename} nie istnieje. Pomijam go.")
            continue

        with open(filename, 'r') as file:
            values = [float(line.strip()) for line in file.readlines()]
        
        # Tworzymy wykres dla każdego pliku
        x_values = list(range(1, len(values) + 1))  # Numerujemy wartości x (1, 2, 3, ...)
        plt.plot(x_values, values, marker='o', linestyle='-', label=f'Z pliku: {filename}')

        # Ustawienia wykresu
        plt.title(f'Wykres z danych z pliku: {filename}')
        plt.xlabel('Indeks')
        plt.ylabel('Wartości')
        plt.grid(True)
        plt.legend()

        # Zapisz wykres w folderze
        output_file = os.path.join(output_folder, f'{os.path.basename(filename)}_wykres.png')
        plt.savefig(output_file)
        plt.clf()  # Czyścimy bieżący wykres, aby nie nałożyły się na siebie

    print(f'Wykresy zostały zapisane w folderze: {output_folder}')

# Sprawdzamy, czy podano nazwę folderu jako argument
if len(sys.argv) < 3:
    print("Proszę podać ścieżkę do folderu z plikami wejściowymi oraz nazwę folderu, w którym chcesz zapisać wykresy.")
    sys.exit(1)

input_folder = sys.argv[1]
output_folder = sys.argv[2]

# Lista plików, które chcesz przetworzyć
filenames = [
    os.path.join(input_folder, 'gauss_elimination_error'),
    os.path.join(input_folder, 'gauss_elimination_with_calculate_b_error'),
    os.path.join(input_folder, 'gauss_elimination_with_main_element_error'),
    os.path.join(input_folder, 'solve_lu_error'),
    os.path.join(input_folder, 'solve_lu_with_main_element_error')
]

plot_and_save_from_files(filenames, output_folder)

