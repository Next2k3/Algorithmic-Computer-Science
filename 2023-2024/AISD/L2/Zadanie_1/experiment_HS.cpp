#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;

int comparisonCount = 0;
int swapCount = 0;

bool compareKeys(int a, int b) {
    comparisonCount++;
    return a < b;
}

void swapKeys(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swapCount++;
}

int partition(vector<int>& arr, int low, int high) {
    int pivotIndex = low + (high - low) / 2;
    int pivot = arr[pivotIndex];
    int i = low;
    int j = high;
    while (true) {
        while (compareKeys(arr[i], pivot )) i++;
        while (compareKeys(pivot, arr[j])) j--;
        if (i >= j) return j;
        swapKeys(&arr[i], &arr[j]);
        i++;
        j--;
    }
}

void insertionSort(vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && compareKeys(key, arr[j])) {
            swapKeys(&arr[j+1], &arr[j]);
            --j;
        }
        arr[j + 1] = key;
    }
}

void hybridSort(vector<int>& arr, int low, int high, int k) {
    if (low < high) {
        if (high - low  <= k) {
            insertionSort(arr, low, high); 
        } else {
            int pi = partition(arr, low, high);
            hybridSort(arr, low, pi, k);
            hybridSort(arr, pi + 1, high, k);
        }
    }
}

int generateNumber(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 2 * n - 1);
    return dis(gen);
}

vector<int> randomNumbers(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = generateNumber(n);
    }
    return arr;
}

int main() {
    int totalSwaps = 0;
    int totalComparisons = 0;

    for (int i = 1; i <= 10; i++) {
        int n = 1000;
        vector<int> initialData = randomNumbers(n);
        vector<int> data = initialData;
        int leastComparisons = 10000000;
        int kComparisons = 0;
        int leastSwaps = 10000000;
        int kSwaps = 0;

        for (int k = 0; k < n / 2; k++) {
            data = initialData;
            hybridSort(data, 0, n - 1, k);
            if (comparisonCount < leastComparisons) {
                leastComparisons = comparisonCount;
                kComparisons = k;
            }
            if (swapCount < leastSwaps) {
                leastSwaps = swapCount;
                kSwaps = k;
            }
            comparisonCount = 0;
            swapCount = 0;
        }

        totalSwaps += kSwaps;
        totalComparisons += kComparisons;

        cout << "Iteration " << i << ": Best k for swaps: " << kSwaps << "; Best k for comparisons: " << kComparisons << endl;
    }

    double avgSwaps = static_cast<double>(totalSwaps) / 10;
    double avgComparisons = static_cast<double>(totalComparisons) / 10;

    cout << endl;
    cout << "Best average k for swaps: " << avgSwaps << endl;
    cout << "Best average k for comparisons: " << avgComparisons << endl;

    return 0;
}