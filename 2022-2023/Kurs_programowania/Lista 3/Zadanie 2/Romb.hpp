#pragma once
#include "Czworokat.hpp"
#include <cmath>
class Romb: public Czworokat{
public:
    Romb(double bok1,double bok2,double bok3,double bok4,double kat);
    double pole();
    double obwod();
    std::string nazwa();
};

