#include <iostream>
#include "WierszTrojkataPascala.hpp"

using namespace std;

WierszTrojkataPascala::WierszTrojkataPascala(int n):n(n) {
    wiersz = new int[n+1];
    for(int i=0;i<n+1;i++){
        wiersz[i]=0;
    }
    wiersz[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j>=1;j--){
            wiersz[j]+=wiersz[j-1];
        }
    }
}
int WierszTrojkataPascala::wspolczynnik(int m) {
    if(m<0 || m>n){
        cout<<m<<" - liczba spoza zakresu"<<endl;
        return -1;
    }
    return wiersz[m];
}
WierszTrojkataPascala::~WierszTrojkataPascala(){
    delete[] wiersz;
}