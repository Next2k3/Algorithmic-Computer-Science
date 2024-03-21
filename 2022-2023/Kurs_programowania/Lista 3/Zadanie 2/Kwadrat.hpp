#pragma once
#include "Czworokat.hpp"

class Kwadrat: public Czworokat{
public:
    Kwadrat(double bok1,double bok2,double bok3,double bok4,double kat);
    double obwod();
    double pole();
    std::string nazwa();
};

