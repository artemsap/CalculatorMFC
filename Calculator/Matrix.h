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

	Matrix(std::vector<std::vector<CEdit*>>& CEditMatrix)
	{
		CreateMatrix(CEditMatrix.size(), CEditMatrix[0].size());
		Convert(CEditMatrix);
	}

	void Resize(int rows, int cols)
	{
		matrix_data.clear();
		CreateMatrix(rows, cols);
	}

	int size()
	{
		return matrix_data.size();
	}

	void Set(int i, int j, T data)
	{
		matrix_data[i][j] = data;
	}

	std::vector<T>& Get(int i)
	{
		return matrix_data[i];
	}

	std::vector<T>& operator[](int i)
	{
		return matrix_data[i];
	}

	template<typename T>
	static Matrix<T> multiply(Matrix<T>& matrix_left, Matrix<T>& matrix_right)
	{
		Matrix<T> matrix_res(matrix_left.size(), matrix_right[0].size());
		for (int i = 0; i != matrix_res.size(); ++i) {
			for (int j = 0; j != matrix_res[0].size(); ++j) {
				T tmp = 0;
				for (int k = 0; k != matrix_right.size(); ++k){
					tmp += matrix_left[i][k] * matrix_right[k][j];
				}
				matrix_res[j][i] = tmp;
			}
		}
		return matrix_res;
	}

	void Convert(std::vector<std::vector<CEdit*>>& CEditMatrix)
	{
		for (int i = 0; i != CEditMatrix.size(); ++i)
		{
			for (int j = 0; j != CEditMatrix[0].size(); ++j)
			{
				CString sWindowText;
				CEditMatrix[i][j]->GetWindowText(sWindowText);
				matrix_data[i][j] = _ttof(sWindowText);
			}
		}
	}

	void ConvertToCEdit(std::vector<std::vector<CEdit*>>& CEditMatrix)
	{
		for (int i = 0; i != CEditMatrix.size(); ++i)
		{
			for (int j = 0; j != CEditMatrix[0].size(); ++j)
			{
				CString sWindowText;
				sWindowText.Format(_T("%g"), matrix_data[i][j]);
				CEditMatrix[i][j]->SetWindowText(sWindowText);
			}
		}
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

