import matplotlib.pyplot as plt
import math
k = 50

def plot_results(file_paths):
    colors = ['red', 'blue', 'black']
    labels = ['k = 1/10 * n', 'k = 9/10 * n', 'k = 1/2 * n' ]

    for idx, file_path in enumerate(file_paths):
        n_values = []
        #comparisons = []
        swaps = []

        with open(file_path, 'r') as file:
            lines = file.readlines()

        color = colors[idx]

        for line in lines:
            data = line.split()
            n_values.append(int(data[0]))
            #comparisons.append(int(data[1]))
            swaps.append(int(data[2]))

        #avg_comparisons = []
        avg_swaps = []

        for i in range(0, len(n_values), k):
            #values_1 = comparisons[i:i + k]
            values_2 = swaps[i:i + k]

            #avg_comparisons.append(sum(values_1) / len(values_1))
            avg_swaps.append(sum(values_2) / len(values_2))
        
        #avg_cmp_n = [s / n for s, n in zip(avg_comparisons, n_values[::k])]
        #avg_swap_n = [s / n for s, n in zip(avg_swaps, n_values[::k])]

        plt.scatter(n_values[::k], avg_swaps, c=color, s=5)

    for idx, label in enumerate(labels):
        plt.scatter([], [], color=colors[idx], label=label)

    plt.xlabel('n')
    plt.ylabel('average swaps')
    plt.title('Average swaps for different k value in Select')
    plt.grid(True)
    plt.legend()
    plt.savefig('avg_swaps_S.png')

file_paths = ["Sresults_k_1_10.txt", "Sresults_k_9_10.txt", "Sresults_k_1_2.txt"]

plot_results(file_paths)