#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

unsigned int comparisonCount = 0;
unsigned int swapCount = 0;

void printArray(const vector<int>& arr) {
    if (arr.size() < 40) {
        for (int key : arr) {
            cout << setw(1) << key << " ";
        }
        cout << endl;
    }
}

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

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}

bool isSorted(const vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void saveDataToFile(int n, unsigned int comparisons, unsigned int swaps) {
    ofstream outputFile("dataQS_n50000_k1.txt", ios_base::app);
    if (outputFile.is_open()) {
        outputFile << n << " ";
        outputFile << comparisons << " ";
        outputFile << swaps << " " << endl;
        outputFile.close();
    } else {
        cout << "Error: Unable to open file for writing!" << endl;
    }
}

int main() {

    ifstream inputFile("random_data_n50000_k1.txt");

    if (!inputFile) {
        cerr << "Unable to open file random_data.txt!" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<int> data;
        int temp;
        while (ss >> temp) {
            data.push_back(temp);
        }

        int n = data.size();

        comparisonCount = 0;
        swapCount = 0;
        vector<int> originalData = data;
        quickSort(data, 0, n - 1);


        if (isSorted(data)) {
            cout << "The array is sorted correctly." << endl;
        } else {
            cout << "Error: The array is not sorted correctly!" << endl;
        }

        saveDataToFile(n, comparisonCount, swapCount);

    }
    return 0;
}
