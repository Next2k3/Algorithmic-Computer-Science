#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

int comparisonCount = 0;
int swapCount = 0;

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
    return a > b;
}

void swapKeys(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swapCount++;
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && compareKeys(arr[j], key)) {
            swapKeys(&arr[j+1], &arr[j]);
            j = j - 1;
        }
        arr[j + 1] = key;
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

void saveDataToFile(int n, int comparisons, int swaps) {
    ofstream outputFile("dataIS_n50_k100.txt", ios_base::app);
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

    ifstream inputFile("random_data_n50_k100.txt");

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
        insertionSort(data);


        if (isSorted(data)) {
            cout << "The array is sorted correctly." << endl;
        } else {
            cout << "Error: The array is not sorted correctly!" << endl;
        }

        saveDataToFile(n, comparisonCount, swapCount);

    }
    return 0;
}
