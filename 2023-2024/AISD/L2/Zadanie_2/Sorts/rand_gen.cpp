#include <iostream>
#include <random>
#include <vector>
#include <stdexcept>
#include <fstream>

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

int main() {
    ofstream outputFile("random_data_n50_k1.txt");

    if (!outputFile) {
        cerr << "Nie można otworzyć pliku do zapisu." << endl;
        return 1;
    }

    for (int n = 10; n <= 50; n += 10) { 
        for (int k = 1; k <= 1; k++) {
            vector<int> randomData = generateRandomData(n);
            for (int data : randomData) {
                outputFile << data << " ";
            }
            outputFile << endl;
        }
    }

    outputFile.close();

    return 0;
}
