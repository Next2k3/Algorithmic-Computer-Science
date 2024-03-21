#pragma once
#include "Figura.hpp"
#include <cmath>

class Szesciokat: public Figura{
private:
    double bok1;
public:
    Szesciokat(double bok1);
    double pole();
    double obwod();
    std::string nazwa();
};

