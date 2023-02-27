#include "pch.h"
#include "../Calculator/Matrix.h"

TEST(TestCaseName, TestName) {
	//Тест, когда матрицы имеют один и тот же размер
	Matrix<int> LeftMatrix(2, 2);
	Matrix<int> RightMatrix(2, 2);

	int cnt = 1;
	for (int i = 0; i != LeftMatrix.size(); ++i) {
		for (int j = 0; j != LeftMatrix[0].size(); ++j) {
			LeftMatrix[i][j] = cnt;
			RightMatrix[i][j] = cnt;
			cnt++;
		}
	}

	Matrix<int> ExpectedResultMatrix(2, 2);
	ExpectedResultMatrix[0][0] = 7;
	ExpectedResultMatrix[0][1] = 10;
	ExpectedResultMatrix[1][0] = 15;
	ExpectedResultMatrix[1][1] = 22;

	auto CurrentResultMatrix = Matrix<int>::multiply(LeftMatrix, RightMatrix);

	EXPECT_EQ(CurrentResultMatrix, ExpectedResultMatrix);

	//Тест, когда у л. матрицы кл-во столбцов = кл-тво строк у пр. матрицы, 
	//кл-во строк л матрицы = кл-во столбцов пр. матрицы

	Matrix<int> LeftMatrix_2(2, 4);
	Matrix<int> RightMatrix_2(4, 2);

	cnt = 1;
	for (int i = 0; i != LeftMatrix_2.size(); ++i) {
		for (int j = 0; j != LeftMatrix_2[0].size(); ++j) {
			LeftMatrix_2[i][j] = cnt;
			cnt++;
		}
	}
	cnt = 1;
	for (int i = 0; i != RightMatrix_2.size(); ++i) {
		for (int j = 0; j != RightMatrix_2[0].size(); ++j) {
			RightMatrix_2[i][j] = cnt;
			cnt++;
		}
	}
	
	Matrix<int> ExpectedResultMatrix_2(2, 2);
	ExpectedResultMatrix_2[0][0] = 50;
	ExpectedResultMatrix_2[0][1] = 60;
	ExpectedResultMatrix_2[1][0] = 114;
	ExpectedResultMatrix_2[1][1] = 140;

	auto CurrentResultMatrix_2 = Matrix<int>::multiply(LeftMatrix_2, RightMatrix_2);

	EXPECT_EQ(CurrentResultMatrix_2, ExpectedResultMatrix_2);

	//Тест, когда у л. матрицы кл-во столбцов = кл-тво строк у пр. матрицы, 
	//кл-во строк л матрицы != кл-во столбцов пр. матрицы
	Matrix<int> LeftMatrix_3(3, 2);
	Matrix<int> RightMatrix_3(2, 4);

	cnt = 1;
	for (int i = 0; i != LeftMatrix_3.size(); ++i) {
		for (int j = 0; j != LeftMatrix_3[0].size(); ++j) {
			LeftMatrix_3[i][j] = cnt;
			cnt++;
		}
	}
	cnt = 1;
	for (int i = 0; i != RightMatrix_3.size(); ++i) {
		for (int j = 0; j != RightMatrix_3[0].size(); ++j) {
			RightMatrix_3[i][j] = cnt;
			cnt++;
		}
	}

	Matrix<int> ExpectedResultMatrix_3(3, 4);
	ExpectedResultMatrix_3[0][0] = 11;
	ExpectedResultMatrix_3[0][1] = 14;
	ExpectedResultMatrix_3[0][2] = 17;
	ExpectedResultMatrix_3[0][3] = 20;
	ExpectedResultMatrix_3[1][0] = 23;
	ExpectedResultMatrix_3[1][1] = 30;
	ExpectedResultMatrix_3[1][2] = 37;
	ExpectedResultMatrix_3[1][3] = 44;
	ExpectedResultMatrix_3[2][0] = 35;
	ExpectedResultMatrix_3[2][1] = 46;
	ExpectedResultMatrix_3[2][2] = 57;
	ExpectedResultMatrix_3[2][3] = 68;

	auto CurrentResultMatrix_3 = Matrix<int>::multiply(LeftMatrix_3, RightMatrix_3);

	EXPECT_EQ(CurrentResultMatrix_3, ExpectedResultMatrix_3);
}