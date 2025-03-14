import matplotlib.pyplot as plt
import math

k = 10

def plot_results(file_paths, type):
    colors = ['green', 'blue', 'red']
    #light_colors = ['lightgreen', 'lightblue']
    labels = ["min", "max", "avg"]

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

        # Plot all values
        # plt.scatter(n_values, kruskal, c=light_colors[0], s=5, alpha=0.6)

        # Calculate and plot averages
        avg_values = []
        min_values = []
        max_values = []
        for i in range(0, len(n_values), k):
            values = kruskal[i:i + k]

            avg_values.append(sum(values) / len(values))
            min_values.append(min(values))
            max_values.append(max(values))

        plt.scatter(n_values[::k], avg_values, c=colors[2], s=5)
        plt.scatter(n_values[::k], min_values, c=colors[0], s=5)
        plt.scatter(n_values[::k], max_values, c=colors[1], s=5)        

    for idx, label in enumerate(labels):
        if idx == 2:
            plt.scatter([], [], color=colors[idx], label=label)

    plt.xlabel('n')
    plt.ylabel(type)
    plt.title('Amount of rounds for different n')
    plt.grid(True)
    plt.legend()
    plt.savefig('avg_' + type + '.png')
    plt.show()

file_paths = ["mst_results2.txt"]

plot_results(file_paths, 'avg')
