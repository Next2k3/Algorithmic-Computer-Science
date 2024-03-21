//
// Created by Paweł on 14.04.2023.
//

#include "Romb.hpp"

Romb::Romb(double bok1, double bok2, double bok3, double bok4, double kat): Czworokat(bok1,bok2,bok3,bok4,kat) {};

double Romb::pole() {
    return bok1*bok1*(sin(kat*M_PI/180.0));
}

double Romb::obwod() {
    return bok1*4;
}

std::string Romb::nazwa() {
    return "Romb";
}