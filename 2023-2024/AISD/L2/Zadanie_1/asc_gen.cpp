#include <iostream>
#include <vector>

using namespace std;

// Funkcja do generowania ciągu liczb posortowanych rosnąco
vector<int> generateSortedData(int n) {
    vector<int> data;
    for (int i = 0; i < n; i++) {
        data.push_back(i);
    }
    return data;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Enter the size of data as an argument." << endl;
        return 1;
    }

    int n;
    try {
        n = stoi(argv[1]);
        if (n <= 0) {
            cerr << "Size of data must be positive." << endl;
            return 1;
        }
    } catch (const invalid_argument& e) {
        cerr << "Invalid argument. Please enter an integer." << endl;
        return 1;
    } catch (const out_of_range& e) {
        cerr << "Out of range." << endl;
        return 1;
    }

    vector<int> sortedData = generateSortedData(n);
    for (int data : sortedData) {
        cout << data << " ";
    }
    cout << endl;

    return 0;
}