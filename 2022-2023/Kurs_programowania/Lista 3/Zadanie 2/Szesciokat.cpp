#include "Szesciokat.hpp"

Szesciokat::Szesciokat(double bok1):bok1(bok1) {};

double Szesciokat::pole() {
    return bok1*bok1*sqrt(3)/4;
}

double Szesciokat::obwod() {
    return 6*bok1;
}

std::string Szesciokat::nazwa() {
    return "Szesciokat";
}