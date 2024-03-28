#include "Zadanie_1_rec.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(int n){
	if(n < 0){
		fprintf(stderr, "Factorial is not defined for negative numbers.\n");
        	exit(EXIT_FAILURE);
	}
	if(n == 0 || n == 1){
		return 1;
	} else {
		return n * factorial(n-1);
	}
}

int gcd(int a,int b){
	if(b == 0){
		return abs(a);
	} else {
		return gcd(b, a % b);
	}
}

DiophantineSolution diophantine(int a, int b, int c){
	DiophantineSolution solution;
	if (a == 0 && b == 0) {
        	fprintf(stderr, "Invalid equation: both coefficients cannot be zero.\n");
        	exit(EXIT_FAILURE);
    	}
    	int gcd_ab = gcd(a, b);
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
    
    if ((c - a * solution.x) % b != 0) {
        DiophantineSolution next_solution = diophantine(b, a % b, c - a * solution.x);
        solution.x += sign_a * next_solution.x;
        solution.y += sign_b * next_solution.y;
    }
    else {
        solution.y = (c - a * solution.x) / b;
    }
    
    return solution;
}
