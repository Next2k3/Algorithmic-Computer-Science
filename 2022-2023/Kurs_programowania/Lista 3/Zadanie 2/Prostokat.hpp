#pragma once
#include "Czworokat.hpp"
class Prostokat: public Czworokat{
public:
    Prostokat(double bok1,double bok2,double bok3,double bok4,double kat);
    double pole();
    double obwod();
    std::string nazwa();
};

