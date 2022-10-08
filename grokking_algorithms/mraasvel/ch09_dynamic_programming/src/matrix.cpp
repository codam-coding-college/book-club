#include "matrix.hpp"
#include <stdexcept>

Matrix::Matrix(int rows, int columns)
: _matrix(rows * columns, 0), _rows(rows), _columns(columns) {}

int& Matrix::get(int row, int col) {
	int index = compute_index(row, col);
	return _matrix[index];
}

int Matrix::get(int row, int col) const {
	int index = compute_index(row, col);
	return _matrix[index];
}

void Matrix::put(int row, int col, int value) {
	int& position = get(row, col);
	position = value;
}

int Matrix::left(int row, int col, int default_value) const {
	if (!is_valid_row_col(row, col-1)) {
		return default_value;
	}
	return _matrix[compute_index_unchecked(row, col-1)];
}

int Matrix::top(int row, int col, int default_value) const {
	if (!is_valid_row_col(row-1, col)) {
		return default_value;
	}
	return _matrix[compute_index_unchecked(row-1, col)];
}

int Matrix::topleft(int row, int col, int default_value) const {
	if (!is_valid_row_col(row-1, col-1)) {
		return default_value;
	}
	return _matrix[compute_index_unchecked(row-1, col-1)];
}

int Matrix::rows() const {
	return _rows;
}
int Matrix::columns() const {
	return _columns;
}

bool Matrix::is_valid_row_col(int row, int col) const {
	return row >= 0 && row < _rows && col >= 0 && col < _columns;
}

int Matrix::compute_index(int row, int col) const {
	if (!is_valid_row_col(row, col)) {
		throw std::runtime_error("matrix: out of bounds access");
	}
	return row * _columns + col;
}

int Matrix::compute_index_unchecked(int row, int col) const {
	return row * _columns + col;
}

void Matrix::debug(std::ostream& out) const {
	out << "[\n";
	for (int row = 0; row < rows(); row++) {
		out << '\t';
		for (int col = 0; col < columns(); col++) {
			if (col > 0) {
				out << ", ";
			}
			out << get(row, col);
		}
		out << '\n';
	}
	out << "]\n";
}
