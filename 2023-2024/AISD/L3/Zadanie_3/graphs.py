import matplotlib.pyplot as plt
import math
k = 50

def plot_results(file_paths):
    colors = ['red', 'blue', 'green', 'black']
    labels = ['p = 3', 'p = 5', 'p = 7', 'p = 9' ]

    for idx, file_path in enumerate(file_paths):
        n_values = []
        #comparisons = []
        #swaps = []
        times = []

        with open(file_path, 'r') as file:
            lines = file.readlines()

        color = colors[idx]

        for line in lines:
            data = line.split()
            n_values.append(int(data[0]))
            #comparisons.append(int(data[1]))
            #swaps.append(int(data[2]))
            times.append(int(data[2]))

        #avg_comparisons = []
        #avg_swaps = []
        avg_times = []

        for i in range(0, len(n_values), k):
            #values_1 = comparisons[i:i + k]
            #values_2 = swaps[i:i + k]
            values_3 = times[i:i + k]

            #avg_comparisons.append(sum(values_1) / len(values_1))
            #avg_swaps.append(sum(values_2) / len(values_2))
            avg_times.append(sum(values_3) / len(values_3))

        plt.scatter(n_values[::k], avg_times, c=color, s=5)

    for idx, label in enumerate(labels):
        plt.scatter([], [], color=colors[idx], label=label)

    plt.xlabel('n')
    plt.ylabel('average times')
    plt.title('Average times for different partition values in Select')
    plt.grid(True)
    plt.legend()
    plt.savefig('avg_times.png')

file_paths = ["Sresults_p_3.txt", "Sresults_p_5.txt", "Sresults_p_7.txt", "Sresults_p_9.txt"]

plot_results(file_paths)