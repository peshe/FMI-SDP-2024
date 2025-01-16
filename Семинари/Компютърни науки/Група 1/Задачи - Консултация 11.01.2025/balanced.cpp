#include <iostream>
#include <vector>

bool isBalanced(const std::vector<std::pair<int, int> > &g, int N) {
	std::vector<int> d_plus(N);
	std::vector<int> d_minus(N);

	for (const std::pair<int, int> &e : g) {
		++d_plus[e.first];
		++d_minus[e.second];
	}

	for (int i = 0; i < N; ++i)
		if (d_plus[i] != d_minus[i] || d_plus[0] == 0) return false;

	return true;
}


bool isEulerian(const std::vector<std::pair<int, int> > &g, int N) {
	std::vector<int> d_plus(N);
	std::vector<int> d_minus(N);

	for (const std::pair<int, int> &e : g) {
		++d_plus[e.first];
		++d_minus[e.second];
	}

	int error1 = 0, error2 = 0;
	for (int i = 0; i < N; ++i) {
		if(d_plus[i] == d_minus[i] && d_plus[i] > 0) {}
		else if(d_plus[i] + 1 == d_minus[i]) {
			++error1;
		} else if(d_plus[i] == d_minus[i] +1) {
			++error2;
		} else {
			return false;
		}
		
	}

	return error1 == error2 && error1 <= 1;
}


int main() {
	/*
4 6

1 2
3 4
2 3
2 4
4 1
4 2
	*/

	std::vector<std::pair<int, int> > g;
	int								  N, M;
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a, b;
		std::cin >> a >> b;
		g.push_back({--a, --b});
	}

	std::cout << isBalanced(g, N) << std::endl;

	std::cout << isEulerian(g, N) << std::endl;
	std::cout << isEulerian(g, N+1) << std::endl;
}
