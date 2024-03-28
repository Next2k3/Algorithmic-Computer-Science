#include <stdio.h>
#include "Zadanie_1_rec.h"

int main(){
	unsigned int n = 5;
	printf("Factorial of %u is %llu\n",n,factorial(n));
	
	unsigned int a = 35, b = 10;
	printf("GCD of %u and %u is %u\n", a, b, gcd(a,b));

	int c = 55;
	DiophantineSolution solution = diophantine(a, b, c);
	printf("Diophantine equation: %dx + %dy = %d is x = %d, y = %d\n",a, b, c, solution.x, solution.y);

	return 0;
}
