#include <iostream>
#include <array>
#include <random>
#include <algorithm>

template<typename T>
struct Range {
	Range(const T min, const T max) : min(min), max(max) {}
	T min;
	T max;
};

template<typename T = size_t>
struct Size {
	Size(const T width, const T height) : width(width), height(height) {}
	T width;
	T height;
};

template<
	typename T, 
	typename Dist, 
	size_t Sz>
std::array<T, Sz> rand_arr(const Range<T> range) {
	std::random_device rd;
	std::mt19937 gen(rd());
	auto dis = Dist(range.min, range.max);
	std::array<T, Sz> values;
	std::generate(begin(values), end(values), [&dis, &gen]() {
		return dis(gen);
	});
	return values;
}

template<
	typename T, 
	size_t Rows,
	size_t Columns
>
std::array<std::array<T, Columns>, Rows> rand_matrix(const Range<T> range) {
	std::array<std::array<T, Columns>, Rows> matrix;
	std::generate(begin(matrix), end(matrix), [&]() {
		return rand_arr<T, std::uniform_real_distribution<>, Columns>(range);
	});
	return matrix;
}


// No dejar

int a[] = { 1, 2, 3, 4, 5 };
int ff = 3;

int popsize = 3;
int npar = 2;
int maxit = 10;
int c1 = 1;
int c2 = 4 - c1; // ??
int c = 1;

int main() {
	auto v = rand_matrix<double, 10, 10>(Range(1.0, 10.0));

	for (const auto& row : v) {
		for (const auto& i : row) {
			std::cout << " " << i;
		}
		std::cout << "\n";
	}
}