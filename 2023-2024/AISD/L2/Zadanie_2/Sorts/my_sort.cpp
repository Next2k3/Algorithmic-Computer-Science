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

vector<int> mergeSortCustom(vector<int>& arr) {
    vector<vector<int>> subsequences;
    vector<int> subsequence;
    subsequence.push_back(arr[0]);

    for (int i = 1; i < arr.size(); ++i) {
        if (compareKeys(arr[i - 1], arr[i])) {
            subsequences.push_back(subsequence);
            subsequence.clear();
            subsequence.push_back(arr[i]);
        } else {
            subsequence.push_back(arr[i]);
        }
    }
    subsequences.push_back(subsequence);

    while (subsequences.size() > 1) {
        vector<vector<int>> mergedSubsequences;
        for (int i = 0; i < subsequences.size(); i += 2) {
            if (i + 1 < subsequences.size()) {
                vector<int> mergedSubsequence = subsequences[i];
                mergedSubsequence.insert(mergedSubsequence.end(), subsequences[i + 1].begin(), subsequences[i + 1].end());
                mergeSort(mergedSubsequence, 0, mergedSubsequence.size() - 1);
                mergedSubsequences.push_back(mergedSubsequence);
            } else {
                mergedSubsequences.push_back(subsequences[i]);
            }
        }
        subsequences = mergedSubsequences;
    }

    return subsequences[0];
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
    ofstream outputFile("dataMYS_n50000_k100.txt", ios_base::app);
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
        data = mergeSortCustom(data);


        if (isSorted(data)) {
            cout << "The array is sorted correctly." << endl;
        } else {
            cout << "Error: The array is not sorted correctly." << endl;
        }

        saveDataToFile(n, comparisonCount, swapCount);

    }
    return 0;
}
