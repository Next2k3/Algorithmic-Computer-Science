#include <iostream>
#include <cmath>
#include "WierszTrojkataPascala.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if(argc<2){
        cout<<argv[1]<<" - Nieprawidlowy liczba parametrow";
        return 0;
    }
    int n;
    try {
        n = atoi(argv[1]);
    }catch(const exception& e){
        cout<<argv[1]<<" - nieprawidlowy numer wiersza"<<endl;
        return 0;
    }
    if(n < 2) {
        cout <<argv[1]<< " - Nieprawidlowy numer wiersza" << endl;
        return 0;
    }
    WierszTrojkataPascala trojkat(n);
    for(int i=2;i<argc;i++){
        int m;
        int wsp;
        try{
            m=stoi(argv[i]);
            try {
                wsp = trojkat.wspolczynnik(m);
                if(wsp>0){
                    cout<<m<<" - "<<wsp<<endl;
                }
            }catch(const invalid_argument& e){
                cout<<m<<" - "<<e.what()<<endl;
            }
        }catch(const exception& e){
            cout<<argv[i]<<" - nieprawidlowe dane"<<endl;
        }
    }
    return 0;
}
