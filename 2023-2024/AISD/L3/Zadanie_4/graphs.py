import matplotlib.pyplot as plt
import math
k = 50


def plot_results(file_paths):
    colors = ['red', 'blue', 'black', 'green']
    labels = ['elements from the beginning', 'elements from the middle', 'elements from the end', 'elements not in '
                                                                                            'array']

    for idx, file_path in enumerate(file_paths):
        n_values = []
        comparisons = []
        # swaps = []

        with open(file_path, 'r') as file:
            lines = file.readlines()

        color = colors[idx]

        for line in lines:
            data = line.split()
            n_values.append(int(data[0]))
            comparisons.append(int(data[2]))
            # swaps.append(int(data[2]))

        avg_comparisons = []
        # avg_swaps = []

        # avg_cmp_n = [s / n for s, n in zip(avg_comparisons, n_values[::k])]
        # avg_swap_n = [s / n for s, n in zip(avg_swaps, n_values[::k])]

        plt.scatter(n_values, comparisons, c=color, s=5)

    for idx, label in enumerate(labels):
        plt.scatter([], [], color=colors[idx], label=label)

    for i in range(1000, 100000, 1000):
        plt.scatter(i, math.log(i) / math.log(2) , c='yellow', s=5)

    plt.xlabel('n')
    plt.ylabel('time')
    plt.title('Time when we search random element based on the position of element')
    plt.grid(True)
    plt.legend()
    plt.savefig('test.png')


file_paths = ["beginning.txt", "middle.txt", "end.txt", "notin.txt"]

plot_results(file_paths)