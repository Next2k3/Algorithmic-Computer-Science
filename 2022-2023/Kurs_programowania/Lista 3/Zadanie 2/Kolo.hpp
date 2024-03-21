#include "Figura.hpp"
#include <cmath>
class Kolo: public Figura{
private:
    double promien;
public:
    Kolo(double promien);
    double obwod();
    double pole();
    std::string nazwa();
};

