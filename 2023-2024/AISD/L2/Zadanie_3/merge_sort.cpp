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

void merge(vector<int>& arr, int low, int mid, int high) {
    int arrayOne = mid - low + 1;
    int arrayTwo = high - mid;

    vector<int> L(arrayOne), R(arrayTwo);

    for (int i = 0; i < arrayOne; i++) {
        L[i] = arr[low + i];
    }
    for (int j = 0; j < arrayTwo; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int indexArrayOne = 0;
    int indexArrayTwo = 0;
    int indexMergedArray = low;

    while (indexArrayOne < arrayOne && indexArrayTwo < arrayTwo) {
        if (compareKeys(L[indexArrayOne], R[indexArrayTwo])) {
            swapKeys(&arr[indexMergedArray], &R[indexArrayTwo]);
            indexArrayTwo++;
        } else {
            arr[indexMergedArray] = L[indexArrayOne];
            indexArrayOne++;
        }
        indexMergedArray++;
    }

    while (indexArrayOne < arrayOne) {
        arr[indexMergedArray] = L[indexArrayOne];
        indexArrayOne++;
        indexMergedArray++;
    }

    while (indexArrayTwo < arrayTwo) {
        arr[indexMergedArray] = R[indexArrayTwo];
        indexArrayTwo++;
        indexMergedArray++;
    }

    printArray(arr);
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
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
    mergeSort(data, 0, n - 1);

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
