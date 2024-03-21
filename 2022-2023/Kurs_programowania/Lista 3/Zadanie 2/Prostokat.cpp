
#include "Prostokat.hpp"

Prostokat::Prostokat(double bok1, double bok2, double bok3, double bok4, double kat): Czworokat(bok1,bok2,bok3,bok4,kat) {};

double Prostokat::pole() {
    return bok1*bok2;
}

double Prostokat::obwod() {
    return bok1*2+bok2*2;
}

std::string Prostokat::nazwa() {
    return "Prostokat";
}