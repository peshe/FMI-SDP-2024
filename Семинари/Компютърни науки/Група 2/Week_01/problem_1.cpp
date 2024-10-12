#include <chrono>
#include <functional>
#include <iostream>

int fib(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;

	return fib(n - 1) + fib(n - 2);
}

int f2_mem[int(1e6)];
int f2(int n) {
	if (f2_mem[n] != 0) return f2_mem[n];

	if (n == 0) return 0;
	if (n == 1) return 1;

	f2_mem[n] = f2(n - 1) + f2(n - 2);
	return f2_mem[n];
}

int f3(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;

	int a = 0, b = 1;
	while (n > 1) {
		int c = a + b;
		a	  = b;
		b	  = c;
		--n;
	}
	return b;
}

int f4(int n) {
	std::function<int(int, int, int)> f4_ = [&f4_](int n, int a, int b) -> int {
		if (n == 1) return b;
		return f4_(n - 1, b, a + b);
	};
	return f4_(n, 0, 1);
}

int main() {
	auto t1 = std::chrono::high_resolution_clock().now();
	for (int i = 0; i < 100; ++i) {
		int a = f3(10000);
	}
	auto t2 = std::chrono::high_resolution_clock().now();
	for (int i = 0; i < 100; ++i) {
		int a = f4(10000);
	}
	auto t3 = std::chrono::high_resolution_clock().now();

	std::cout << "f3: " << t2 - t1 << std::endl;
	std::cout << "f4: " << t3 - t2 << std::endl;
}
