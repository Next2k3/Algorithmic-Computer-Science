#include "Kwadrat.hpp"
Kwadrat::Kwadrat(double bok1, double bok2, double bok3, double bok4, double kat): Czworokat(bok1,bok2,bok3,bok4,kat) {};

double Kwadrat::obwod() {
    return bok1*4;
}
double Kwadrat::pole() {
    return bok1*bok1;
}

std::string Kwadrat::nazwa() {
    return "Kwadrat";
}