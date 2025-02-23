import matplotlib.pyplot as plt
import numpy as np

def parse_data(filename):
    data = {}
    with open(filename, "r") as file:
        for line in file:
            k, i, matching, time = map(float, line.split())
            k, i = int(k), int(i)
            if k not in data:
                data[k] = {}
            if i not in data[k]:
                data[k][i] = {"matching": [], "time": []}
            data[k][i]["matching"].append(matching)
            data[k][i]["time"].append(time)
    return data

def plot_matching_vs_i(data, output_dir="plots"):
    for k, i_data in data.items():
        i_values = sorted(i_data.keys())
        avg_matchings = [np.mean(i_data[i]["matching"]) for i in i_values]

        plt.figure(figsize=(8, 5))
        plt.plot(i_values, avg_matchings, marker='o', label=f"k={k}")
        plt.title(f"Maksymalne skojarzenie w zależności od i (k={k})")
        plt.xlabel("i")
        plt.ylabel("Maksymalne skojarzenie")
        plt.grid(True)
        plt.savefig(f"{output_dir}/matching_for_k_{k}.png")
        plt.close()

def plot_time_vs_k(data, output_dir="plots"):
    all_i_values = {i for k_data in data.values() for i in k_data.keys()}

    for i in sorted(all_i_values):
        k_values = []
        avg_times = []

        for k, i_data in data.items():
            if i in i_data:
                k_values.append(k)
                avg_times.append(np.mean(i_data[i]["time"]))

        plt.figure(figsize=(8, 5))
        plt.plot(k_values, avg_times, marker='o', label=f"i={i}")
        plt.title(f"Czas w zależności od k (i={i})")
        plt.xlabel("k")
        plt.ylabel("Czas (ms)")
        plt.grid(True)
        plt.savefig(f"{output_dir}/time_for_i_{i}.png")
        plt.close()

def main():
    input_file = "testResults.txt"  # Plik wejściowy
    output_dir = "plots"     # Katalog na wykresy

    # Parsowanie danych z pliku
    data = parse_data(input_file)

    # Generowanie wykresów
    plot_matching_vs_i(data, output_dir)
    plot_time_vs_k(data, output_dir)

    print(f"Wykresy zostały zapisane w katalogu '{output_dir}'.")

if __name__ == "__main__":
    main()
