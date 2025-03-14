import matplotlib.pyplot as plt
import math

k = 5

def plot_results(file_paths, type):
    colors = ['green', 'blue']
    light_colors = ['lightgreen', 'lightblue']
    labels = ["Kruskal's algorithm", "Prim's algorithm"]

    for idx, file_path in enumerate(file_paths):
        n_values = []
        kruskal = []
        prim = []

        with open(file_path, 'r') as file:
            lines = file.readlines()

        for line in lines:
            data = line.split()
            n_values.append(int(data[0]))
            kruskal.append(int(data[1]))
            prim.append(int(data[2]))

        # Plot all values
        plt.scatter(n_values, kruskal, c=light_colors[0], s=5, alpha=0.6)
        plt.scatter(n_values, prim, c=light_colors[1], s=5, alpha=0.6)

        # Calculate and plot averages
        avg_values = []
        for i in range(0, len(n_values), k):
            values = kruskal[i:i + k]

            avg_values.append(sum(values) / len(values))

        plt.scatter(n_values[::k], avg_values, c=colors[0], s=5)

        avg_values = []
        for i in range(0, len(n_values), k):
            values = prim[i:i + k]

            avg_values.append(sum(values) / len(values))

        plt.scatter(n_values[::k], avg_values, c=colors[1], s=5)
        

    for idx, label in enumerate(labels):
        plt.scatter([], [], color=colors[idx], label=label + ' (average)')
        plt.scatter([], [], color=light_colors[idx], label=label, alpha=0.6)

    plt.xlabel('n')
    plt.ylabel(type)
    plt.title('Average ' +type + " for Prim's and Kruskal's algorithm")
    plt.grid(True)
    plt.legend()
    plt.savefig('avg_' + type + '.png')
    plt.show()

file_paths = ["mst_results.txt"]

plot_results(file_paths, 'time')
