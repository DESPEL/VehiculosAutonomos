#include <array>
#include <vector>
#include <random>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <random>


template <typename T, size_t Rows, size_t Columns>
class Matrix {

	using Representation = std::array<std::array<T, Columns>, Rows>;
	using Table = Matrix<T, Rows, Columns>;
	Representation data;
public:
	using type = T;
    using value_type = T;

	static Table zeros() {
		Table result;
		for (auto& column: result)
			for (auto& value: column)
				value = T();
		return result;
	}

	template<typename Function>
	void fill(Function func) {
		for (auto& row: data)
			for (auto& v: row)
				v = func();
	}

    T dot_product(Matrix<T, 1, Columns>& rhs) {
        double result = 0;
        for (int i = 0; i != Columns; ++i)
            result += data[0][i] * rhs[0][i];
        return result;
    }

    T dot_product(Matrix<T, 1, Columns>&& rhs) {
        double result = 0;
        for (int i = 0; i != Columns; ++i)
            result += data[0][i] * rhs[0][i];
        return result;
    }

	typename Representation::iterator begin() {
		return data.begin();
	}
	
	typename Representation::iterator end() {
		return data.end();
	}

	std::array<T, Columns>& operator[](size_t row) {
		return data[row];
	}

	Matrix<T, Rows, Columns> operator+(Table& rhs) {
		Matrix<T, Rows, Columns> result;
		for (int i = 0; i < Rows; ++i)
			for (int j = 0; j < Columns; ++j)
				result[i][j] = data[i][j] + rhs[i][j];
		return result;
	}

    template<typename U>
    Matrix<T, Rows, Columns> operator+(U rhs) {
		Matrix<T, Rows, Columns> result;
		for (int i = 0; i < Rows; ++i)
			for (int j = 0; j < Columns; ++j)
				result[i][j] = data[i][j] + rhs;
		return result;
	}

	Matrix<T, Rows, Columns> operator-(Table& rhs) {
		Matrix<T, Rows, Columns> result;
		for (int i = 0; i < Rows; ++i)
			for (int j = 0; j < Columns; ++j)
				result[i][j] = data[i][j] - rhs[i][j];
		return result;
	}

	template<size_t R, size_t C>
	Matrix<T, Rows, Rows> operator*(Matrix<T, R, C>& rhs) {
        static_assert(Columns == R);

		Matrix<T, Rows, Rows> result;
		for (int i = 0; i < Rows; ++i) 
			for (int j = 0; j < C; ++j) 
				for (int k = 0; k < R; ++k) 
					result[i][j] += data[i][k] * rhs[k][j];
		return result;
	}

    template<size_t R, size_t C>
	Matrix<T, Rows, Rows> operator*(Matrix<T, R, C>&& rhs) {
        static_assert(Columns == R);

		Matrix<T, Rows, Rows> result;
		for (int i = 0; i < Rows; ++i) 
			for (int j = 0; j < C; ++j) 
				for (int k = 0; k < R; ++k) 
					result[i][j] += data[i][k] * rhs[k][j];
		return result;
	}

    Table operator *(double rhs) {
        Table result;
        for (int i = 0; i != Rows; ++i)
            for (int j = 0; j != Columns; ++j)
                result[i][j] = data[i][j] * rhs;
        return result;
    }

};