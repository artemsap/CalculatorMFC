#pragma once
#include <vector>

template<typename T>
class Matrix
{
public:
	Matrix(int rows, int cols)
	{
		CreateMatrix(rows, cols);
	}

	const int size() const
	{
		return matrix_data.size();
	}

	std::vector<T>& operator[](int i)
	{
		return matrix_data[i];
	}

	const std::vector<T>& operator[](int i) const
	{
		return matrix_data[i];
	}

	template<typename T>
	static Matrix<T> multiply(Matrix<T>& matrix_left, Matrix<T>& matrix_right)
	{
		Matrix<T> matrix_res(matrix_left.size(), matrix_right[0].size());
		for (int j = 0; j != matrix_res[0].size(); ++j) {
			for (int i = 0; i != matrix_res.size(); ++i) {
				T tmp = 0;
				for (int k = 0; k != matrix_right.size(); ++k){
					tmp += matrix_left[i][k] * matrix_right[k][j];
				}
				matrix_res[i][j] = tmp;
			}
		}
		return matrix_res;
	}

	bool operator== (const Matrix<T> matrix_left) const
	{
		if (matrix_left.size() != matrix_data.size())
			return false;

		for (int i = 0; i != matrix_left.size(); ++i)
		{
			if (matrix_left[i].size() != matrix_data[i].size())
				return false;
		}

		for (int i = 0; i != matrix_left.size(); ++i)
		{
			for (int j = 0; j != matrix_left[i].size(); ++j)
			{
				if (matrix_left[i][j] != matrix_data[i][j])
					return false;
			}
		}

		return true;
	}

private:
	std::vector<std::vector<T>> matrix_data;

	void CreateMatrix(int rows, int cols)
	{
		for (int i = 0; i != rows; ++i)
		{
			std::vector<T> tmp_vector;
			for (int j = 0; j != cols; ++j)
			{
				tmp_vector.push_back(0);
			}
			matrix_data.push_back(tmp_vector);
		}
	}

};

