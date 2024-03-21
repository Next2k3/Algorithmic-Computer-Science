#pragma once
#include "Figura.hpp"

class Czworokat: public Figura{
protected:
    double bok1,bok2,bok3,bok4,kat;
public:
    Czworokat(double bok1,double bok2,double bok3,double bok4,double kat);
    std::string nazwa();
};

