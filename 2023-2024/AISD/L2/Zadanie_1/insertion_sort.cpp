#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

int comparisonCount = 0;
int swapCount = 0;

void printArray(const vector<int>& arr) {
    if (arr.size() < 40) {
        for (int key : arr) {
            cout << setw(2) << key << " ";
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

        printArray(arr);
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

int main() {
    string input;
    getline(cin, input);
    stringstream ss(input);
    vector<int> data;
    int temp;
    while (ss >> temp) {
        data.push_back(temp);
    }
    
    int n = data.size();
    cout << "Original array: ";
    printArray(data);
    cout << endl;

    vector<int> originalData = data;
    insertionSort(data);

    cout << endl;

    if (isSorted(data)) {
        cout << "The array is sorted correctly." << endl;
    } else {
        cout << "Error: The array is not sorted correctly!" << endl;
    }
    cout << endl;
    
    cout << "Original array: ";
    printArray(originalData);

    cout << "Sorted array:   ";
    printArray(data);

    cout << endl;

    cout << "Comparisons: " << comparisonCount << endl;
    cout << "Swaps:       " << swapCount << endl;

    return 0;
}