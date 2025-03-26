#include <iostream>

using namespace std;

int f(int k) {
	return k;
}

int sumIter(int n) {
	int sum = 0;
	for (int k = 0; k <= n; k++) {
		sum += f(k);
	}
	return sum;
}

int sumRec(int n) {
	if (n == 0) return f(0);
	return f(n) + sumRec(n-1);
}

int main() {
	int n = 5;
	std::cout<< "Suma Iteracyjnie: " << sumIter(n) << std::endl;
	std::cout<< "Suma Rekurencyjnie: " << sumRec(n) << std::endl;
	return 0;
}
