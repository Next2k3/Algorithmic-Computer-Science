#include <iostream>
#include <cmath>
#include "LiczbyPierwsze.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "Brak argumentow" << endl;
        return 0;
    }
    int n;
    try{
        n=atoi(argv[1]);
    }catch(const invalid_argument&){
        cout << "Nieprawidlowy zakres" << endl;
        return 0;
    }
    if(n < 2) {
        cout << "Nieprawidlowy zakres" << endl;
        return 0;
    }
    LiczbyPierwsze lp(n);
    for(int i=2; i<argc; i++) {
        int argument;
        try {
            argument = stoi(argv[i]);
        } catch (const invalid_argument&) {
            cout << argv[i] << " - nieprawidlowa dana" << endl;
            continue;
        }
        try {
            int pierwsza = lp.liczba(argument);
            if(pierwsza!=-1){
                cout << argument << " - " << pierwsza << endl;
            }
        } catch (const invalid_argument& e) {
            cout << argument << " - " << e.what() << endl;
        }

    }
    return 0;
}
