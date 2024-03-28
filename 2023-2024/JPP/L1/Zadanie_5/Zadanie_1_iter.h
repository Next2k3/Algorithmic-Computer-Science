#ifndef ZAD_1_ITER
#define ZAD_1_ITER

typedef struct{
	int x;
	int y;
} DiophantineSolution;

unsigned long factorial(int n);
int gcd(int a,int b);
DiophantineSolution diophantine(int a,int b,int c);

#endif /* ZAD_1_ITER_H */
