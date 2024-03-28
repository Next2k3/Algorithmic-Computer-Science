#include "Zadanie_1_iter.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long factorial(int n){
	if (n < 0) {
        	fprintf(stderr, "Factorial is not defined for negative numbers.\n");
        	exit(EXIT_FAILURE);
    	}
	unsigned long result =1;
	for(int i=2;i <= n; ++i){
		result *= i;
	}
	return result;
}

int gcd(int a,int b){
	while(b != 0){
		int temp = b;
		b = a % b;
		a = temp;
	}
	return abs(a);
}

DiophantineSolution diophantine(int a,int b,int c){
	DiophantineSolution solution;
	if (a == 0 && b == 0) {
        	fprintf(stderr, "Invalid equation: both coefficients cannot be zero.\n");
        	exit(EXIT_FAILURE);
    	}
	int gcd_ab = gcd(a,b);
	if (c % gcd_ab != 0) {
        	fprintf(stderr, "No solution: c is not divisible by gcd(a, b).\n");
        	exit(EXIT_FAILURE);
    	}
	int sign_a = a < 0 ? -1 : 1;
	int sign_b = b < 0 ? -1 : 1;
	a = abs(a);
	b = abs(b);
	int div = c / gcd_ab;
	solution.x = sign_a * div;
	solution.y = 0;
	while ((c - a * solution.x) % b != 0) {
        	solution.x += sign_a * (b / gcd_ab);
        	solution.y -= sign_b * (a / gcd_ab);
    	}
    	solution.y = (c - a * solution.x) / b;
	return solution;
}
