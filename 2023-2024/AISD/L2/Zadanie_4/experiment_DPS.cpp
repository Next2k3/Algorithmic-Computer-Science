#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
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

int partition(vector<int>& arr, int low, int high, int* lp){
    if (arr[low] > arr[high]) {
        swapKeys(&arr[low], &arr[high]);
    }
    int p = arr[low]; //lewy pivot
    int q = arr[high]; // prawy pivot
    int i = low + 1; // iterator
    int k = low + 1; // iterator
    int g = high - 1; // iteratory
    int l = 0; // counter
    int s = 0; // counter
    while (k <= g){

        // jezeli liczba elementow duzych (wiekszych od q) wieksza od liczby elementow malych (mniejszych od p)
        // najpierw porownaj z q, potem w razie potrzeby z p
        if (l > s){ 
            if (compareKeys(q, arr[k])) {
                while (compareKeys(q, arr[g]) && k < g) g--;
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
                while (compareKeys(q, arr[g]) && k < g) g--;
                swapKeys(&arr[k], &arr[g]);
                l++;
                g--;
                if(compareKeys(arr[k], p)){
                    swapKeys(&arr[k], &arr[i]);
                    i++;
                    s++;
                }
            }
        } 
        k++;
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
    //printArray(arr);
    return g;
}

// funkcja dzielaca problem sortowania na trzy podproblemy
void dualPivotQuickSort(vector<int>& arr, int low, int high){
    int n = arr.size();
    if (low < high) {
        int lp, rp;
        rp = partition(arr, low, high, &lp);
        dualPivotQuickSort(arr, low, lp-1);
        dualPivotQuickSort(arr, lp + 1, rp -1);
        dualPivotQuickSort(arr, rp + 1, high);
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

double countConstant(int n) {
    return comparisonCount / (n * log(n));
}

void constantExperiment() {
    comparisonCount = 0;
    double k = 0;
    for (int i = 10; i <= 1000; i = i + 10) {
        vector<int> arr = randomNumbers(i);
        dualPivotQuickSort(arr, 0, arr.size() - 1);
        k += countConstant(arr.size());
        comparisonCount = 0;
    }
    cout << "Constant k: " << k/100 << endl;
}

int main() {

    for (int i = 1; i <= 5; i++) {
        constantExperiment();
    }

    //constantExperiment();

    return 0;
}
