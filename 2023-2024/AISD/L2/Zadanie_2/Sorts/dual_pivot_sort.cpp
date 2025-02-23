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
    return a < b;
}

void swapKeys(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swapCount++;
}

int partition(vector<int>& arr, int low, int high, int* lp){
    if (arr[low] > arr[high]) {
        swapKeys(&arr[low], &arr[high]);
    }
    int p = arr[low]; //lewy pivot
    int q = arr[high]; // prawy pivot
    int i = low + 1; // iterator
    int indexMergedArray = low + 1; // iterator
    int g = high - 1; // iteratory
    int l = 0; // counter
    int s = 0; // counter
    while (k <= g){

        // jezeli liczba elementow duzych (wiekszych od q) wieksza od liczby elementow malych (mniejszych od p)
        // najpierw porownaj z q, potem w razie potrzeby z p
        if (l > s){ 
            if (compareKeys(q, arr[k])) {
                while (compareKeys(q, arr[g]) && k < g) {
                    g--;
                } 
                swapKeys(&arr[k], &arr[g]);
                l++;
                g--;
                if(compareKeys(arr[k], p)){
                    swapKeys(&arr[k], &arr[i]);
                    i++;
                    s++;
                }
            }
            else if(compareKeys(arr[k], p)){
                swapKeys(&arr[k], &arr[i]);
                s++;
                i++;
            }
        }
        // jezeli liczba elementow duzych (wiekszych od q) mniejsza/rowna od liczby elementow malych (mniejszych od p)
        // najpierw porownaj z p, potem w razie potrzeby z q
        else { 
            if(compareKeys(arr[k], p)){
                swapKeys(&arr[k], &arr[i]);
                s++;
                i++;
            }
            else if(compareKeys(q, arr[k])) {
                while (compareKeys(q, arr[g]) && k < g) {
                    g--;
                }
                swapKeys(&arr[k], &arr[g]);
                l++;
                g--;
                if(compareKeys(arr[k], p)){
                    swapKeys(&arr[k], &arr[i]);
                    i++;
                    s++;
                }
            }
        } k++;
    }
    i--;
    g++;
    if (low != i) {
        swapKeys(&arr[low], &arr[i]);
    }
    if (high != g) {
        swapKeys(&arr[high], &arr[g]);
    }

    *lp = i;
    return g;
}

// funkcja dzielaca problem sortowania na trzy podproblemy
void dualPivotQuickSort(vector<int>& arr, int low, int high){
    if (low < high) {
        int lp, rp;
        rp = partition(arr, low, high, &lp);
        dualPivotQuickSort(arr, low, lp-1);
        dualPivotQuickSort(arr, lp + 1, rp -1);
        dualPivotQuickSort(arr, rp + 1, high);
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
    ofstream outputFile("dataDPS_n50_k1.txt", ios_base::app);
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

    ifstream inputFile("random_data_n50_k1.txt");

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
        dualPivotQuickSort(data, 0, n - 1);


        if (isSorted(data)) {
            cout << "The array is sorted correctly." << endl;
        } else {
            cout << "Error: The array is not sorted correctly!" << endl;
        }

        saveDataToFile(n, comparisonCount, swapCount);

    }
    return 0;
}
