#Program modified if necessary.
import matplotlib.pyplot as plt

def plot_results(file_paths):
    colors = ['b', 'r', 'g', 'black']
    labels = ['Insertion Sort', 'Quick Sort', 'Hybrid Sort', 'Dual Pivot Quick Sort']

    for idx, file_path in enumerate(file_paths):
        n_values = []
        cmp = []
        swap = []

        with open(file_path, 'r') as file:
            lines = file.readlines()

        color = colors[idx]

        for line in lines:
            data = line.split()
            n_values.append(int(data[0]))
            cmp.append(int(data[1]))  
            swap.append(int(data[2]))

        avg_cmp = []
        avg_swap = []

        for i in range(0, len(n_values), 1):
            values_1_slice = cmp[i:i + 1]
            values_2_slice = swap[i:i + 1]

            avg_cmp.append(sum(values_1_slice) / len(values_1_slice))
            avg_swap.append(sum(values_2_slice) / len(values_2_slice))

        avg_cmp_n = [s / n for s, n in zip(avg_cmp, n_values[::1])]
        avg_swap_n = [s / n for s, n in zip(avg_swap, n_values[::1])]

        plt.scatter(n_values[::1], avg_swap, c=color, s=25)
        #plt.scatter(n_values[::1], avg_swap_n, c=color, s=25)

    for idx, label in enumerate(labels):
        plt.scatter([], [], color=colors[idx], label=label)

    plt.xlabel('n')
    #plt.ylabel('liczba przestawień / n')
    plt.ylabel('liczba przestawień')
    plt.title('Porównanie złożoności algorytmów sortowania. (k = 1)')
    plt.grid(True)
    plt.legend()
    plt.show()

file_paths = ["dataIS_n50_k1.txt", "dataQS_n50_k1.txt", "dataHS_n50_k1.txt", "dataDPS_n50_k1.txt"] 
plot_results(file_paths)
