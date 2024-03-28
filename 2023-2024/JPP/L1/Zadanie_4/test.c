#include "Zadanie_4.h"
#include <stdio.h>

int main() {
    	unsigned int N = 5; 

    	printf("Factorial(%d) = %d\n", N, wrapped_factorial(N));

	unsigned int A = 35, B = 10;
    	printf("GCD(%d, %d) = %d\n", A, B, wrapped_gcd(A, B));

	unsigned int C = 55;
    	DiophantineSolution solution = wrapped_diophantine(A, B, C);
    	printf("Diophantine solution: X = %d, Y = %d\n", solution.X, solution.Y);

    	return 0;
}

