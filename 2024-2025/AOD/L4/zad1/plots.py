import matplotlib.pyplot as plt

def load_data(filename):
    """Wczytuje dane z pliku tekstowego."""
    k = []
    average_flow = []
    average_paths = []
    average_time = []

    with open(filename, 'r') as file:
        for line in file:
            if line.strip():  # Pomijamy puste linie
                parts = line.split()
                k.append(int(parts[0]))
                average_flow.append(float(parts[1]))
                average_paths.append(float(parts[2]))
                average_time.append(float(parts[3]))
    
    return k, average_flow, average_paths, average_time


def plot_data(k, data, label, title, xlabel, ylabel, figsize):
    """Tworzy i zapisuje wykres dla danych."""
    plt.figure(figsize=figsize)
    plt.plot(k, data, marker='o', linestyle='-', color='b', label=label)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
    plt.legend()
    plt.show()


def main():
    # Nazwa pliku z danymi
    input_file = "testResults.txt"  # Podmień na nazwę swojego pliku

    # Rozmiar wykresów (zmień, jeśli chcesz inne proporcje)
    figsize = (10, 6)

    # Wczytujemy dane z pliku
    k, average_flow, average_paths, average_time = load_data(input_file)

    # Generujemy wykresy
    plot_data(
        k, average_flow, "Average Flow",
        "Średni przepływ w zależności od k",
        "k", "Średni przepływ", figsize
    )

    plot_data(
        k, average_paths, "Average Paths Count",
        "Średnia liczba ścieżek w zależności od k",
        "k", "Średnia liczba ścieżek", figsize
    )

    plot_data(
        k, average_time, "Average Time",
        "Średni czas działania w zależności od k",
        "k", "Średni czas (s)", figsize
    )


if __name__ == "__main__":
    main()
