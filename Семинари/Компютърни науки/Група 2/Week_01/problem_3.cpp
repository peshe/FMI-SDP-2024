#include <chrono>
#include <iostream>

int arr[10][1000000];

int main() {
	int	 s;
	auto t1 = std::chrono::high_resolution_clock().now();
	{
		s = 0;
		for (int i = 0; i < 100; ++i) {
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 1000000; ++j) {
					s += arr[i][j];
				}
			}
		}
	}

	auto t2 = std::chrono::high_resolution_clock().now();
	{
		s = 0;
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 1000000; ++j) {
				for (int i = 0; i < 10; ++i) {
					s += arr[i][j];
				}
			}
		}
	}
	auto t3 = std::chrono::high_resolution_clock().now();

	std::cout << "1: " << t2 - t1 << std::endl;
	std::cout << "2: " << t3 - t2 << std::endl;
}
