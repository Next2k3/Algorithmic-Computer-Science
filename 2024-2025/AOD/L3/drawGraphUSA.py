import matplotlib.pyplot as plt
import os
import numpy as np

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
    results = {"radixHeap": {}, "dijkstra": {}, "dial": {}}
    regions = set()

    for filename in os.listdir(directory):
        if filename.endswith(".radixheap.ss.res"):
            method = "radixHeap"
        elif filename.endswith(".dijkstra.ss.res"):
            method = "dijkstra"
        elif filename.endswith(".dial.ss.res"):
            method = "dial"
        else:
            continue

        # Wyciągnięcie regionu z nazwy pliku (np. USA-road-t.BAY -> BAY)
        region = filename.split('.')[1]
        regions.add(region)

        # Wyciągnięcie czasu wykonania, z pominięciem brakujących plików
        try:
            time = extract_time_from_file(os.path.join(directory, filename))
            results[method][region] = time
        except (FileNotFoundError, ValueError):
            print(f"Warning: Skipping file {filename} due to error or missing data.")

    # Obliczenie średnich czasów dla sortowania
    avg_times = {region: np.mean([results[method].get(region, float('inf')) 
                                  for method in results]) for region in regions}
    # Sortowanie regionów po średnich czasach
    sorted_regions = sorted(regions, key=lambda r: avg_times[r])

    # Uzupełnienie brakujących danych jako None
    for method in results:
        results[method] = [results[method].get(region, None) for region in sorted_regions]

    return sorted_regions, results

def plot_results(x_values, results, name, log=False, limit = 0):
    """
    Rysuje wykres porównujący czasy wykonania dla różnych metod.
    """
    plt.figure(figsize=(12, 6))
    for method, times in results.items():
        # Filtruje brakujące dane (None)
        filtered_x = [x for x, t in zip(x_values, times) if t is not None]
        filtered_times = [t for t in times if t is not None]
        plt.plot(filtered_x, filtered_times, marker='o', label=method)

    if log:
        plt.yscale('log')
    
    if limit != 0:
        plt.ylim(0, limit)

    plt.xlabel("Region")
    plt.ylabel("Execution Time (seconds)")
    plt.title(f"Comparison of Shortest Path Algorithms for {name}")
    plt.xticks(rotation=45)
    plt.legend()
    plt.grid(True)

    # Zapis wykresu
    if log:
        plt.savefig(f"/home/pawe/Pulpit/Algorithmic-Computer-Science/2024-2025/AOD/L3/test13/graphs/log/{name}_graph_log_scale.png")
    elif limit != 0:
        plt.savefig(f"/home/pawe/Pulpit/Algorithmic-Computer-Science/2024-2025/AOD/L3/test13/graphs/limit/{name}_graph_scale_with_limit.png")
    else:
        plt.savefig(f"/home/pawe/Pulpit/Algorithmic-Computer-Science/2024-2025/AOD/L3/test13/graphs/normal/{name}_graph.png")

if __name__ == "__main__":
    results_directory = "/home/pawe/Pulpit/Algorithmic-Computer-Science/2024-2025/AOD/L3/test13/results/USA-road-t"
    name = "USA-road-t"
    limit = 0.005
    x_values, results = parse_files(results_directory)
    plot_results(x_values, results, name, log=True)  # Wykres w skali logarytmicznej
    plot_results(x_values, results, name, log=False)  # Wykres liniowy
    plot_results(x_values, results, name, False, limit)

