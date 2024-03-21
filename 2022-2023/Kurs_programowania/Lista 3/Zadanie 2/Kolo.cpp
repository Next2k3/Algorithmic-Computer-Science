//
// Created by Paweł on 14.04.2023.
//

#include "Kolo.hpp"
#include <cmath>

Kolo::Kolo(double promien):promien(promien){}

double Kolo::obwod() {
    return 2*M_PI*promien;
}

double Kolo::pole() {
    return M_PI*promien*promien;
}

std::string Kolo::nazwa() {
    return "Kolo";
}