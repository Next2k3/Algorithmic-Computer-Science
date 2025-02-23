#include <iostream>
#include <random>
#include <vector>
#include <stdexcept>

using namespace std;

// Funkcja do generowania losowych danych do posortowania
vector<int> generateRandomData(int n) {
    vector<int> data;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 2 * n - 1);

    for (int i = 0; i < n; i++) {
        data.push_back(dis(gen));
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

    vector<int> randomData = generateRandomData(n);
    for (int data : randomData) {
        cout << data << " ";
    }
    cout << endl;

    return 0;
}