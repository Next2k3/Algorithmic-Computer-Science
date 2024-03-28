#ifndef ZAD_1_REC
#define ZAD_1_REC

typedef struct{
	int x;
	int y;
} DiophantineSolution;

unsigned long long factorial(int n);
int gcd(int a,int b);
DiophantineSolution diophantine(int a,int b,int c);

#endif /* ZAD_1_REC_H */
