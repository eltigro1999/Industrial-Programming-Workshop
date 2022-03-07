#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void Greetings();
void InputMatrixSize(int& N, int& M, const std::string& MatrixName);
void CreateMatrix(int**& Matrix, const int& N, const int& M);
void FillMatrixManually(int**& Matrix, const int& N, const int& M);
void RandomFillMatrix(int**& Matrix, const int& N, const int& M);
void DrawMatrix(const std::string& MatrixName, int**& const Matrix, const int& N, const int& M);
void FillReducedMatrix(int**& ReducedMatrix, const int& ReducedMatrixSize, int**& const Matrix, const int& MatrixSizeN, const int& MatrixSizeM);
void FillSubmatrix1(int**& Submatrix, const int& SubmatrixSize, int**& const ReducedMatrix);
void FillSubmatrix2(int**& Submatrix, const int& SubmatrixSize, int**& const ReducedMatrix);
void FillSubmatrix3(int**& Submatrix, const int& SubmatrixSize, int**& const ReducedMatrix);
void FillSubmatrix4(int**& Submatrix, const int& SubmatrixSize, int**& const ReducedMatrix);
void FormatResultantMatrix(int**& const ResultantMatrix, const int& InitialMatrixSize, int& CurrentPosition, int& FormattedMatrixSize);
void DefineIntermediateMatrixValues25(int**& MatrixToChange, const int& MatrixToChangeSize, int**& const LeftSubmatrix1, int**& const LeftSubmatrix2,
	int**& const RightSubmatrix, const int& i, const int& j) {
	for (int z = 0; z < MatrixToChangeSize; z++)
	{
		MatrixToChange[i][j] += (LeftSubmatrix1[i][z] + LeftSubmatrix2[i][z]) * RightSubmatrix[z][j];
	}
}
void DefineIntermediateMatrixValues34(int**& MatrixToChange, const int& MatrixToChangeSize, int**& const LeftSubmatrix, int**& const RightSubmatrix1,
	int**& const RightSubmatrix2, const int& i, const int& j) {
	for (int z = 0; z < MatrixToChangeSize; z++)
	{
		MatrixToChange[i][j] += LeftSubmatrix[i][z] * (RightSubmatrix1[z][j] - RightSubmatrix2[z][j]);
	}
}
void DefineIntermediateMatrixValues67(int**& MatrixToChange, const int& MatrixToChangeSize, int**& const LeftSubmatrix1, int**& const LeftSubmatrix2,
	int**& const RightSubmatrix1, int**& const RightSubmatrix2, const int& i, const int& j) {
	for (int z = 0; z < MatrixToChangeSize; z++)
	{
		MatrixToChange[i][j] += (LeftSubmatrix1[i][z] - LeftSubmatrix2[i][z]) * (RightSubmatrix1[z][j] + RightSubmatrix2[z][j]);
	}
}



void main()
{
	srand(time(NULL));
	int LeftMatrixSizeN, LeftMatrixSizeM, RightMatrixSizeN, RightMatrixSizeM, ReducedMatrixSize = 2;
	bool ManuallyInput;
	system("chcp 1251");

	Greetings();

	InputMatrixSize(LeftMatrixSizeN, LeftMatrixSizeM, std::string("первой"));
	InputMatrixSize(RightMatrixSizeN, RightMatrixSizeM, std::string("второй"));

	int** LeftMatrix;
	int** RightMatrix;
	CreateMatrix(LeftMatrix, LeftMatrixSizeN, LeftMatrixSizeM);
	CreateMatrix(RightMatrix, RightMatrixSizeN, RightMatrixSizeM);


	cout << "Выберите способ заполнения матриц\n" <<
		"0 - Случайным образом\n" <<
		"Любое число, отличное от нуля - Вручную \n";

	cin >> ManuallyInput;

	if (ManuallyInput) {
		FillMatrixManually(LeftMatrix, LeftMatrixSizeN, LeftMatrixSizeM);
		FillMatrixManually(RightMatrix, RightMatrixSizeN, RightMatrixSizeM);
	}
	else {
		RandomFillMatrix(LeftMatrix, LeftMatrixSizeN, LeftMatrixSizeM);
		RandomFillMatrix(RightMatrix, RightMatrixSizeN, RightMatrixSizeM);
	}
	DrawMatrix(std::string("Матрица 1"), LeftMatrix, LeftMatrixSizeN, LeftMatrixSizeM);
	DrawMatrix(std::string("Матрица 2"), RightMatrix, RightMatrixSizeN, RightMatrixSizeM);


	while (ReducedMatrixSize < LeftMatrixSizeN || ReducedMatrixSize < RightMatrixSizeN
		|| ReducedMatrixSize < LeftMatrixSizeM || ReducedMatrixSize < RightMatrixSizeM)
		ReducedMatrixSize *= 2;
	int** LeftMatrixReduced;
	int** RightMatrixReduced;
	CreateMatrix(LeftMatrixReduced, ReducedMatrixSize, ReducedMatrixSize);
	CreateMatrix(RightMatrixReduced, ReducedMatrixSize, ReducedMatrixSize);
	FillReducedMatrix(LeftMatrixReduced, ReducedMatrixSize, LeftMatrix, LeftMatrixSizeN, LeftMatrixSizeM);
	FillReducedMatrix(RightMatrixReduced, ReducedMatrixSize, RightMatrix, RightMatrixSizeN, RightMatrixSizeM);

	cout << "Приведенные матрицы\n";
	DrawMatrix(std::string("Матрица 1"), LeftMatrixReduced, ReducedMatrixSize, ReducedMatrixSize);
	DrawMatrix(std::string("Матрица 2"), RightMatrixReduced, ReducedMatrixSize, ReducedMatrixSize);

	/////////////////////

	int** LeftSubmatrix1;
	int** LeftSubmatrix2;
	int** LeftSubmatrix3;
	int** LeftSubmatrix4;
	int** RightSubmatrix1;
	int** RightSubmatrix2;
	int** RightSubmatrix3;
	int** RightSubmatrix4;

	CreateMatrix(LeftSubmatrix1, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(RightSubmatrix1, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(LeftSubmatrix2, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(RightSubmatrix2, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(LeftSubmatrix3, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(RightSubmatrix3, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(LeftSubmatrix4, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(RightSubmatrix4, ReducedMatrixSize / 2, ReducedMatrixSize / 2);

	FillSubmatrix1(LeftSubmatrix1, ReducedMatrixSize / 2, LeftMatrixReduced);
	FillSubmatrix1(RightSubmatrix1, ReducedMatrixSize / 2, RightMatrixReduced);
	FillSubmatrix2(LeftSubmatrix2, ReducedMatrixSize / 2, LeftMatrixReduced);
	FillSubmatrix2(RightSubmatrix2, ReducedMatrixSize / 2, RightMatrixReduced);
	FillSubmatrix3(LeftSubmatrix3, ReducedMatrixSize / 2, LeftMatrixReduced);
	FillSubmatrix3(RightSubmatrix3, ReducedMatrixSize / 2, RightMatrixReduced);
	FillSubmatrix4(LeftSubmatrix4, ReducedMatrixSize / 2, LeftMatrixReduced);
	FillSubmatrix4(RightSubmatrix4, ReducedMatrixSize / 2, RightMatrixReduced);

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////Создание промежуточных матриц//////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** IntermediateMatrix1;
	int** IntermediateMatrix2;
	int** IntermediateMatrix3;
	int** IntermediateMatrix4;
	int** IntermediateMatrix5;
	int** IntermediateMatrix6;
	int** IntermediateMatrix7;

	CreateMatrix(IntermediateMatrix1, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(IntermediateMatrix2, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(IntermediateMatrix3, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(IntermediateMatrix4, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(IntermediateMatrix5, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(IntermediateMatrix6, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(IntermediateMatrix7, ReducedMatrixSize / 2, ReducedMatrixSize / 2);

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Вычисление значений промежуточных матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < ReducedMatrixSize / 2; i++)
	{
		for (int j = 0; j < ReducedMatrixSize / 2; j++)
		{
			IntermediateMatrix1[i][j] = 0;
			IntermediateMatrix2[i][j] = 0;
			IntermediateMatrix3[i][j] = 0;
			IntermediateMatrix4[i][j] = 0;
			IntermediateMatrix5[i][j] = 0;
			IntermediateMatrix6[i][j] = 0;
			IntermediateMatrix7[i][j] = 0;

			for (int z = 0; z < ReducedMatrixSize / 2; z++)
			{
				IntermediateMatrix1[i][j] += (LeftSubmatrix1[i][z] + LeftSubmatrix4[i][z]) * (RightSubmatrix1[z][j] + RightSubmatrix4[z][j]);
			}
			DefineIntermediateMatrixValues25(IntermediateMatrix2, ReducedMatrixSize / 2, LeftSubmatrix3,
				LeftSubmatrix4, RightSubmatrix1, i, j);
			DefineIntermediateMatrixValues34(IntermediateMatrix3, ReducedMatrixSize / 2, LeftSubmatrix1,
				RightSubmatrix2, RightSubmatrix4, i, j);
			DefineIntermediateMatrixValues34(IntermediateMatrix3, ReducedMatrixSize / 2, LeftSubmatrix4,
				RightSubmatrix3, RightSubmatrix1, i, j);
			DefineIntermediateMatrixValues25(IntermediateMatrix5, ReducedMatrixSize / 2, LeftSubmatrix1,
				LeftSubmatrix2, RightSubmatrix4, i, j);
			DefineIntermediateMatrixValues67(IntermediateMatrix6, ReducedMatrixSize / 2, LeftSubmatrix3,
				LeftSubmatrix1, RightSubmatrix1, RightSubmatrix2, i, j);
			DefineIntermediateMatrixValues67(IntermediateMatrix7, ReducedMatrixSize / 2, LeftSubmatrix2,
				LeftSubmatrix4, RightSubmatrix3, RightSubmatrix4, i, j);
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////Создание вспомогательных матриц/////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** AuxiliaryMatrix1;
	int** AuxiliaryMatrix2;
	int** AuxiliaryMatrix3;
	int** AuxiliaryMatrix4;
	CreateMatrix(AuxiliaryMatrix1, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(AuxiliaryMatrix2, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(AuxiliaryMatrix3, ReducedMatrixSize / 2, ReducedMatrixSize / 2);
	CreateMatrix(AuxiliaryMatrix4, ReducedMatrixSize / 2, ReducedMatrixSize / 2);

	///////////////////////////////////////////////////////////////////////////////
	////////////Подсчет значений вспомогательных матриц из промежуточных///////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < ReducedMatrixSize / 2; i++)
	{
		for (int j = 0; j < ReducedMatrixSize / 2; j++)
		{
			AuxiliaryMatrix1[i][j] = IntermediateMatrix1[i][j] + IntermediateMatrix4[i][j] - IntermediateMatrix5[i][j] + IntermediateMatrix7[i][j];
			AuxiliaryMatrix2[i][j] = IntermediateMatrix3[i][j] + IntermediateMatrix5[i][j];
			AuxiliaryMatrix3[i][j] = IntermediateMatrix2[i][j] + IntermediateMatrix4[i][j];
			AuxiliaryMatrix4[i][j] = IntermediateMatrix1[i][j] - IntermediateMatrix2[i][j] + IntermediateMatrix3[i][j] + IntermediateMatrix6[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Создание результирующей матрицы/////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** ResultantMatrix;
	CreateMatrix(ResultantMatrix, ReducedMatrixSize, ReducedMatrixSize);

	///////////////////////////////////////////////////////////////////////////////
	///////Занесение информации из вспомогательных матриц в результирующую/////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < ReducedMatrixSize / 2; i++)
	{
		for (int j = 0; j < ReducedMatrixSize / 2; j++)
		{
			ResultantMatrix[i][j] = AuxiliaryMatrix1[i][j];
			ResultantMatrix[i][j + ReducedMatrixSize / 2] = AuxiliaryMatrix2[i][j];
			ResultantMatrix[i + ReducedMatrixSize / 2][j] = AuxiliaryMatrix3[i][j];
			ResultantMatrix[i + ReducedMatrixSize / 2][j + ReducedMatrixSize / 2] = AuxiliaryMatrix4[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выравнивание границ результирующей матрицы/////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int CurrentPosition = 0, FinalRowAmount = 100, FinalColumnAmount = 100;
	FormatResultantMatrix(ResultantMatrix, ReducedMatrixSize, CurrentPosition, FinalRowAmount);
	FormatResultantMatrix(ResultantMatrix, ReducedMatrixSize, CurrentPosition, FinalColumnAmount);

	int** FormattedResultantMatrix;
	CreateMatrix(FormattedResultantMatrix, FinalRowAmount, FinalColumnAmount);
	for (int i = 0; i < FinalRowAmount; i++)
	{
		for (int j = 0; j < FinalColumnAmount; j++)
			FormattedResultantMatrix[i][j] = ResultantMatrix[i][j];
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Вывод результирующей матрицы////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	DrawMatrix(std::string("Результирующая матрица"), FormattedResultantMatrix, FinalRowAmount, FinalColumnAmount);
	system("pause");

	///////////////////////////////////////////////////////////////////////////////
	/////////////////////Очистка динамической памяти///////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < LeftMatrixSizeN; i++)
		delete[] LeftMatrix[i];
	for (int i = 0; i < RightMatrixSizeN; i++)
		delete[] RightMatrix[i];
	for (int i = 0; i < ReducedMatrixSize; i++)
	{
		delete[] LeftMatrixReduced[i];
		delete[] RightMatrixReduced[i];
		delete[] ResultantMatrix[i];
	}
	for (int i = 0; i < FinalRowAmount; i++)
		delete[] FormattedResultantMatrix[i];
	for (int i = 0; i < ReducedMatrixSize / 2; i++)
	{
		delete[] LeftSubmatrix1[i];
		delete[] LeftSubmatrix2[i];
		delete[] LeftSubmatrix3[i];
		delete[] LeftSubmatrix4[i];
		delete[] RightSubmatrix1[i];
		delete[] RightSubmatrix2[i];
		delete[] RightSubmatrix3[i];
		delete[] RightSubmatrix4[i];
		delete[] AuxiliaryMatrix1[i];
		delete[] AuxiliaryMatrix2[i];
		delete[] AuxiliaryMatrix3[i];
		delete[] AuxiliaryMatrix4[i];
		delete[] IntermediateMatrix1[i];
		delete[] IntermediateMatrix2[i];
		delete[] IntermediateMatrix3[i];
		delete[] IntermediateMatrix4[i];
		delete[] IntermediateMatrix5[i];
		delete[] IntermediateMatrix6[i];
		delete[] IntermediateMatrix7[i];
	}
	delete[] LeftMatrix, RightMatrix, LeftMatrixReduced, RightMatrixReduced, ResultantMatrix, FormattedResultantMatrix;
	delete[] LeftSubmatrix1, LeftSubmatrix2, LeftSubmatrix3, LeftSubmatrix4, RightSubmatrix1, RightSubmatrix2, RightSubmatrix3, RightSubmatrix4, AuxiliaryMatrix1, AuxiliaryMatrix2, AuxiliaryMatrix3, AuxiliaryMatrix4;
	delete[] IntermediateMatrix1, IntermediateMatrix2, IntermediateMatrix3, IntermediateMatrix4, IntermediateMatrix5, IntermediateMatrix6, IntermediateMatrix7;
}

void Greetings() {
	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";
}

void InputMatrixSize(int& N, int& M, const std::string& MatrixName) {
	do
	{
		cout << "Введите размеры " << MatrixName << " матрицы\n";
		cin >> N >> M;
	} while (N <= 0 || M <= 0);
}

void CreateMatrix(int**& Matrix, const int& N, const int& M) {
	Matrix = new int* [N];
	for (int i = 0; i < N; i++)
		Matrix[i] = new int[M];
}

void FillMatrixManually(int**& Matrix, const int& N, const int& M) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> Matrix[i][j];
}

void RandomFillMatrix(int**& Matrix, const int& N, const int& M) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			Matrix[i][j] = rand() % 10;
}

void DrawMatrix(const std::string& MatrixName, int**& const Matrix, const int& N, const int& M) {
	cout << "\n" << MatrixName << "\n\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << Matrix[i][j] << " ";
		cout << endl;
	}
}

void FillReducedMatrix(int**& ReducedMatrix, const int& ReducedMatrixSize, int**& const Matrix, const int& MatrixSizeN, const int& MatrixSizeM) {
	for (int i = 0; i < ReducedMatrixSize; i++)
	{
		for (int j = 0; j < ReducedMatrixSize; j++)
			ReducedMatrix[i][j] = 0;
	}
	for (int i = 0; i < MatrixSizeN; i++)
	{
		for (int j = 0; j < MatrixSizeM; j++)
			ReducedMatrix[i][j] = Matrix[i][j];
	}
}

void FillSubmatrix1(int**& Submatrix, const int& SubmatrixSize, int**& const ReducedMatrix) {
	for (int i = 0; i < SubmatrixSize; i++)
	{
		for (int j = 0; j < SubmatrixSize; j++)
			Submatrix[i][j] = ReducedMatrix[i][j];
	}
}

void FillSubmatrix2(int**& Submatrix, const int& SubmatrixSize, int**& const ReducedMatrix) {
	for (int i = 0; i < SubmatrixSize; i++)
	{
		for (int j = 0; j < SubmatrixSize; j++)
			Submatrix[i][j] = ReducedMatrix[i][j + SubmatrixSize];
	}
}

void FillSubmatrix3(int**& Submatrix, const int& SubmatrixSize, int**& const ReducedMatrix) {
	for (int i = 0; i < SubmatrixSize; i++)
	{
		for (int j = 0; j < SubmatrixSize; j++)
			Submatrix[i][j] = ReducedMatrix[i + SubmatrixSize][j];
	}
}

void FillSubmatrix4(int**& Submatrix, const int& SubmatrixSize, int**& const ReducedMatrix) {
	for (int i = 0; i < SubmatrixSize; i++)
	{
		for (int j = 0; j < SubmatrixSize; j++)
			Submatrix[i][j] = ReducedMatrix[i + SubmatrixSize][j + SubmatrixSize];
	}
}

void FormatResultantMatrix(int**& const ResultantMatrix, const int& InitialMatrixSize, int& CurrentPosition, int& FormattedMatrixSize) {
	for (int i = 0; i < InitialMatrixSize; i++)
	{
		CurrentPosition = 0;
		for (int j = 0; j < InitialMatrixSize; j++)
		{
			if (ResultantMatrix[j][i] != 0)
			{
				CurrentPosition++;
				FormattedMatrixSize = 100;
			}
		}
		if (CurrentPosition == 0 && i < FormattedMatrixSize)
		{
			FormattedMatrixSize = i;
		}
	}
}
