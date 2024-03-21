#pragma once
#include "Figura.hpp"
#include <cmath>

class Pieciokat: public Figura{
private:
    double bok1;
public:
    Pieciokat(double bok1);
    double pole();
    double obwod();
    std::string nazwa();
};

