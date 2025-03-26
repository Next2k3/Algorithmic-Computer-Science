#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
	double y = sin(x);
	return y * y + y + x; 
}

double f2(double x) {
	return sin(x) * (sin(x) + 1) + x;
}

int main() {
	cout << "f1: " << f(1.0) << endl;
	cout << "f2; " << f2(1.0) << endl;
	return 0;
}
