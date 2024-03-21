#include <iostream>
#include "LiczbyPierwsze.hpp"
using namespace std;

LiczbyPierwsze::LiczbyPierwsze(int n){
    bool* zlozone =new bool[n+1];
    for(int i=0;i<n+1;i++){
        zlozone[i]=false;
    }
    ilosc =0;
    for(int i=2;i<=n;i++){
        if(!zlozone[i]){
            ilosc++;
            for(int j=i*i;j<=n;j+=i){
                zlozone[j]=true;
            }
        }
    }
    pierwsze =new int[ilosc];
    int indeks =0;
    for(int i=2;i<=n;i++){
        if(!zlozone[i]){
            pierwsze[indeks]=i;
            indeks++;
        }
    }
    delete[] zlozone;
}
int LiczbyPierwsze::liczba(int m){
    if(m<0 || m>=ilosc){
        cout<<m<<"- liczba spoza zakresu"<<endl;
        return -1;
    }
    return pierwsze[m];
}
LiczbyPierwsze::~LiczbyPierwsze(){
    delete[] pierwsze;
}