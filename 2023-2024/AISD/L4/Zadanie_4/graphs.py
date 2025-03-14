import matplotlib.pyplot as plt
import math

k = 20

def plot_results(file_paths, type):
    colors = ['red', 'blue']
    light_colors = ['lightcoral', 'lightblue']
    labels = ['increasing keys', 'random keys']

    for idx, file_path in enumerate(file_paths):
        n_values = []
        if type == 'comparisons':
            comparisons = []
        elif type == 'reads':
            reads = []
        elif type == 'assignments':
            assignments = []
        elif type == 'heights':
            heights = []

        with open(file_path, 'r') as file:
            lines = file.readlines()

        for line in lines:
            data = line.split()
            n_values.append(int(data[0]))
            if type == 'comparisons':
                comparisons.append(int(data[1]))
            elif type == 'reads':
                reads.append(int(data[2]))
            elif type == 'assignments':
                assignments.append(int(data[3]))
            elif type == 'heights':
                heights.append(int(data[4]))

        # Plot all values
        if type == 'comparisons':
            plt.scatter(n_values, comparisons, c=light_colors[idx], s=5, alpha=0.6)
        elif type == 'reads':
            plt.scatter(n_values, reads, c=light_colors[idx], s=5, alpha=0.6)
        elif type == 'assignments':
            plt.scatter(n_values, assignments, c=light_colors[idx], s=5, alpha=0.6)
        elif type == 'heights':
            plt.scatter(n_values, heights, c=light_colors[idx], s=5, alpha=0.6)

        # Calculate and plot averages
        avg_values = []
        for i in range(0, len(n_values), k):
            if type == 'comparisons':
                values = comparisons[i:i + k]
            elif type == 'reads':
                values = reads[i:i + k]
            elif type == 'assignments':
                values = assignments[i:i + k]
            elif type == 'heights':
                values = heights[i:i + k]

            avg_values.append(sum(values) / len(values))

        if type == 'comparisons':
            plt.scatter(n_values[::k], avg_values, c=colors[idx], s=5)
        elif type == 'reads':
            plt.scatter(n_values[::k], avg_values, c=colors[idx], s=5)
        elif type == 'assignments':
            plt.scatter(n_values[::k], avg_values, c=colors[idx], s=5)
        elif type == 'heights':
            plt.scatter(n_values[::k], avg_values, c=colors[idx], s=5)

    for idx, label in enumerate(labels):
        plt.scatter([], [], color=colors[idx], label=label)
        plt.scatter([], [], color=light_colors[idx], label=label + ' (all values)', alpha=0.6)

    plt.xlabel('n')
    plt.ylabel('average ' + type)
    plt.title('Average ' + type + ' for different keys in Red-Black Binary Search Tree')
    plt.grid(True)
    plt.legend()
    plt.savefig('avg_' + type + '.png')
    plt.show()

file_paths = ["outputAsc.txt", "outputRand.txt"]

#plot_results(file_paths, 'comparisons')
#plot_results(file_paths, 'reads')
#plot_results(file_paths, 'assignments')
plot_results(file_paths, 'heights')
