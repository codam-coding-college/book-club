#pragma once

#include <vector>
#include <ostream>

class Matrix {
	public:
		Matrix(int rows, int columns);

	private:
		int& get(int row, int col);

	public:
		int get(int row, int col) const;
		void put(int row, int col, int value);
		int rows() const;
		int columns() const;

		// functions return default if missing, otherwise value
		int left(int row, int col, int default_value) const;
		int top(int row, int col, int default_value) const;
		int topleft(int row, int col, int default_value) const;

		void debug(std::ostream& out) const;

	private:
		bool is_valid_row_col(int row, int col) const;
		int compute_index(int row, int col) const;
		int compute_index_unchecked(int row, int col) const;

	private:
		std::vector<int> _matrix;
		int _rows;
		int _columns;
};
