#include <iostream>
#include "Kolo.hpp"
#include "Kwadrat.hpp"
#include "Romb.hpp"
#include "Prostokat.hpp"
#include "Pieciokat.hpp"
#include "Szesciokat.hpp"

using namespace std;

int main(int argc,char *argv[]) {
    cout<<argv[1]<<endl;

    if(argv[1][0]=='o') {
        double promien;
        try {
            promien = atoi(argv[2]);
        } catch (const exception &e) {
            cout << argv[2] << " - nieprawidłowy promien" << endl;
            return 0;
        }
        Kolo kolo(promien);
        cout<<kolo.nazwa()<<endl;
        cout <<"Pole: "<< kolo.pole() << endl;
        cout <<"Obowod: "<< kolo.obwod() << endl;
    }
    else if(argv[1][0]=='c'){
        double bok1,bok2,bok3,bok4,kat;

        try{
            bok1=atoi(argv[2]);
            bok2=atoi(argv[3]);
            bok3=atoi(argv[4]);
            bok4=atoi(argv[5]);
            kat=atoi(argv[6]);
        }catch(const exception &e){
            cout<<"błędne argumenty"<<endl;
            return 0;
        }
        if(bok1==bok2 && bok2==bok3 && bok3==bok4){
            if(kat==90) {
                Kwadrat kwadrat(bok1,bok2,bok3,bok4,kat);
                cout<<kwadrat.nazwa()<<endl;
                cout <<"Pole: "<< kwadrat.pole() << endl;
                cout <<"Obowod: "<< kwadrat.obwod() << endl;
            }
            else{
                Romb romb(bok1,bok2,bok3,bok4,kat);
                cout<<romb.nazwa()<<endl;
                cout<<"Pole: "<<romb.pole()<<endl;
                cout<<"Obowod: "<<romb.obwod()<<endl;
            }
        }
        else if(bok1==bok2 && bok3==bok4 && kat==90){
            Prostokat prostokat(bok1,bok3,bok2,bok4,kat);
            cout<<prostokat.nazwa()<<endl;
            cout<<"Pole: "<<prostokat.pole()<<endl;
            cout<<"Obowod: "<<prostokat.obwod()<<endl;
        }
        else if(bok1==bok3 && bok2==bok4 && kat==90){
            Prostokat prostokat(bok1,bok2,bok3,bok4,kat);
            cout<<prostokat.nazwa()<<endl;
            cout<<"Pole: "<<prostokat.pole()<<endl;
            cout<<"Obowod: "<<prostokat.obwod()<<endl;
        }
    }
    else if(argv[1][0]=='p'){
        double bok1;
        try{
            bok1=atoi(argv[2]);
        }catch(const exception &e){
            cout<<"błędne argumenty"<<endl;
            return 0;
        }
        Pieciokat pieciokat(bok1);
        cout<<pieciokat.nazwa()<<endl;
        cout<<"Pole: "<<pieciokat.pole()<<endl;
        cout<<"Obowod: "<<pieciokat.obwod()<<endl;
    }
    else if(argv[1][0]=='s'){
        double bok1;
        try{
            bok1=atoi(argv[2]);
        }catch(const exception &e){
            cout<<"błędne argumenty"<<endl;
            return 0;
        }
        Szesciokat szesciokat(bok1);
        cout<<szesciokat.nazwa()<<endl;
        cout<<"Pole: "<<szesciokat.pole()<<endl;
        cout<<"Obowod: "<<szesciokat.obwod()<<endl;
    }

    return 0;
}
