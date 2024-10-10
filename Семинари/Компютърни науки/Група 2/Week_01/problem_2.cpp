#include <iostream>


long long mem[int(1e4)][int(1e4)];

long long sumVariations(int n, int max) {
	if(mem[n][max]) return mem[n][max];

	if(n == 0) {
		mem[n][max] = 1;
		return 1;
	}
	long long sum = 0;
	for(int i = 1; i <= std::min(max, n); ++i) {
		sum += sumVariations(n - i, i);
	}

	mem[n][max] = sum;
	return sum;
}

long long sumVariations(int n) {
	return sumVariations(n, n);
}

int main() {
	int n;
	std::cin >> n;
	std::cout << sumVariations(n) << std::endl;
}
