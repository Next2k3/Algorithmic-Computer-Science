#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>

const int INSERTION_SORT_THRESHOLD = 10;

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

void hybridSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        if (high - low <= INSERTION_SORT_THRESHOLD) {
            insertionSort(arr, low, high); 
        } else {
            int pi = partition(arr, low, high);
            hybridSort(arr, low, pi);
            hybridSort(arr, pi + 1, high);
            }
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
    ofstream outputFile("dataHS_n50000_k100.txt", ios_base::app);
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

    ifstream inputFile("random_data_n50000_k100.txt");

    if (!inputFile) {
        cerr << "Unable to open file." << endl;
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
        hybridSort(data, 0, n - 1);


        if (isSorted(data)) {
            cout << "The array is sorted correctly." << endl;
        } else {
            cout << "Error: The array is not sorted correctly." << endl;
        }

        saveDataToFile(n, comparisonCount, swapCount);

    }
    return 0;
}
