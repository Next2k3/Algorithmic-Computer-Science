import matplotlib.pyplot as plt
import os

def extract_time_from_file(filename):
    """
    Odczytuje czas wykonania z ostatniej linii pliku wynikowego.
    """
    with open(filename, 'r') as file:
        lines = file.readlines()
        for line in lines:
            if line.startswith("t"):
                return float(line.split()[1])
    raise ValueError(f"No execution time found in {filename}")

def parse_files(directory):
    """
    Wczytuje pliki z katalogu i zwraca słownik z czasami wykonania
    dla różnych metod (radixHeap, dijkstra, dial).
    Obsługuje brakujące pliki, pomijając je.
    """
    results = {"radixHeap": [], "dijkstra": [], "dial": []}
    x_values_set = set()

    for filename in os.listdir(directory):
        if filename.endswith(".radixheap.ss.res"):
            method = "radixHeap"
        elif filename.endswith(".dijkstra.ss.res"):
            method = "dijkstra"
        elif filename.endswith(".dial.ss.res"):
            method = "dial"
        else:
            continue

        # Wyciągnięcie wartości z nazwy pliku (np. longc_0 -> 0)
        x_value = int(filename.split('_')[1].split('.')[0])
        x_values_set.add(x_value)

        # Wyciągnięcie czasu wykonania, z pominięciem brakujących plików
        try:
            time = extract_time_from_file(os.path.join(directory, filename))
            results[method].append((x_value, time))
        except (FileNotFoundError, ValueError):
            print(f"Warning: Skipping file {filename} due to error or missing data.")

    # Posortowanie wyników względem wartości X
    x_values = sorted(list(x_values_set))
    for method in results:
        method_results = {x: None for x in x_values}  # Domyślnie None dla brakujących wyników
        for x, time in results[method]:
            method_results[x] = time
        results[method] = [method_results[x] for x in x_values]

    return x_values, results

def plot_results(x_values, results, type, name, log = False, limit = 0):
    """
    Rysuje wykres porównujący czasy wykonania dla różnych metod.
    """
    plt.figure(figsize=(10, 6))
    for method, times in results.items():
        # Filtruje brakujące dane (None)
        filtered_x = [x for x, t in zip(x_values, times) if t is not None]
        filtered_times = [t for t in times if t is not None]
        plt.plot(filtered_x, filtered_times, marker='o', label=method)

    if log == True:
        plt.yscale('log')

    if limit != 0:
        plt.ylim(0, limit)

    plt.xlabel("Input Size")
    plt.ylabel("Execution Time (seconds)")
    plt.title(f"Comparison of Shortest Path Algorithms for {name} family")
    plt.legend()
    plt.grid(True)

    if log == True:
        plt.savefig(f"/home/pawe/Pulpit/Algorithmic-Computer-Science/2024-2025/AOD/L3/test13/graphs/log/{type}_graph_log_scale.png")
    elif limit != 0:
        plt.savefig(f"/home/pawe/Pulpit/Algorithmic-Computer-Science/2024-2025/AOD/L3/test13/graphs/limit/{type}_graph_scale_with_limit.png")
    else:
        plt.savefig(f"/home/pawe/Pulpit/Algorithmic-Computer-Science/2024-2025/AOD/L3/test13/graphs/normal/{type}_graph.png")

if __name__ == "__main__":
    # Zmień "results_directory" na katalog z wynikami

    types = ["longc", "longn", "random4c", "random4n", "squarec", "squaren"]
    names = ["Long-C", "Long-n", "Random4-C", "Random4-n", "Square-C", "Square-n"]
    limits = [0.002, 0.004, 0.002, 0.004, 0.002, 0.004]
    for i in range(len(types)):
        results_directory = (f"/home/pawe/Pulpit/Algorithmic-Computer-Science/2024-2025/AOD/L3/test13/results/{types[i]}")
        x_values, results = parse_files(results_directory)
        plot_results(x_values, results, types[i], names[i], True)
        plot_results(x_values, results, types[i], names[i], False)
        plot_results(x_values, results, types[i], names[i], False, limits[i])
