#pragma once
#include <iostream>

class Figura {
public:
    virtual double pole()=0;
    virtual double obwod()=0;
    virtual std::string nazwa()=0;
};

