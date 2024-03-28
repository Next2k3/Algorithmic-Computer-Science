#ifndef ZADANIE_4_H
#define ZADANIE_4_H

typedef struct {
    int X;
    int Y;
} DiophantineSolution;

extern int Factorial(int N);
extern int GCD(int A, int B);
extern DiophantineSolution Diophantine(int A, int B, int C);

int wrapped_factorial(int n);
int wrapped_gcd(int a,int b);
DiophantineSolution wrapped_diophantine(int a,int b,int c);

#endif /* ZADANIE_4_H */

