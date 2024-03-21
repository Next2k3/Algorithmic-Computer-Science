//
// Created by Paweł on 14.04.2023.
//

#include "Pieciokat.hpp"
Pieciokat::Pieciokat(double bok1):bok1(bok1) {};

double Pieciokat::pole() {
    return bok1*(sqrt(5)+1)/2;
}

double Pieciokat::obwod() {
    return 5*bok1;
}

std::string Pieciokat::nazwa() {
    return "Pieciokat";
}