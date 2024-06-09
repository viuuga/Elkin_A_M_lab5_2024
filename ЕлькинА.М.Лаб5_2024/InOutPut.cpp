/*
Елькин Александр Михайлович ИВТ-11БО 2024


Реализованно задание 1

*/

//функции ввода ввывода


#include"InOutPut.h"
#include<iostream>
#include<cstdio>
#include<fstream>



void output_rat_mat(std::vector<std::vector<RationalFraction>>& matrix)
{

	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[0].size(); ++j) {
			std::cout << matrix[i][j] << " ";
		}
		printf("\n");
	}
}


void output_int_mat(std::vector<std::vector<int>>& matrix)
{
	int size = matrix.size();

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		printf("\n");
	}
}

void output_polynomial(std::vector<RationalFraction>& pol)
{
	std::cout << "\nМногочлен:\n";
	RationalFraction nul(0, 1);
	int deg = pol.size();
	for (int i = 1; i <= deg; ++i) {

		if (pol[i - 1].getNumerator() > 0 && pol[i - 1].getDenominator() > 0) {
			if (i != 1)
				std::cout << " +";
			std::cout << pol[i - 1] << "x^" << deg - i;
		}
		else if (pol[i - 1].getNumerator() < 0 && pol[i - 1].getDenominator() < 0) {
			if (i != 1)
				std::cout << " +";
			std::cout << pol[i - 1] << "x^" << deg - i;
		}
		else if (pol[i - 1].getNumerator() < 0 && pol[i - 1].getDenominator() > 0) {
			std::cout << pol[i - 1] << "x^" << deg - i;
		}
		else if (pol[i - 1].getNumerator() > 0 && pol[i - 1].getDenominator() < 0) {
			std::cout << pol[i - 1] << "x^" << deg - i;
		}
	}
	std::cout << std::endl;
}


void output_pol_roots(std::vector<std::pair<RationalFraction, int>>& roots) {
	std::cout << std::endl;
	if (roots.size() == 0) std::cout << "There are no rational roots" << std::endl;
	for (std::pair<RationalFraction, int>& root : roots) {
		std::cout << "Root: " << root.first << ", Algebraic degree: " << root.second << std::endl;
	}
}


int input_rat_mat_file(std::vector<std::vector<RationalFraction>>& matrix, char fname[256])
{
	char fir, sec;
	int msize, prov;
	FILE* file;
	fopen_s(&file, fname, "r+");
	if (!file) {
		return -2;
	}


	fscanf_s(file, " %c", &fir);
	fscanf_s(file, " %c", &sec);
	prov = fscanf_s(file, "%d", &msize);
	if (prov < 1)
		return -1;
	matrix.resize(msize, std::vector<RationalFraction>(msize));

	char simb;
	int el;
	for (int i = 0; i < msize; ++i) {
		for (int j = 0; j < msize; ++j) {
			prov = fscanf_s(file, "%d", &el);
			if (prov < 1)
				return -1;
			matrix[i][j].setNumerator(el);
			fscanf_s(file, "%c", &simb);
			if (simb == '/') {
				prov = fscanf_s(file, "%d", &el);
				if (prov < 1)
					return -1;
				matrix[i][j].setDenominator(el);
			}
		}
	}

	return 1;
}


int input_rat_mat(std::vector<std::vector<RationalFraction>>& matrix, std::string fname)
{
	std::string fir, sec;
	int msize;
	std::ifstream file;
	file.open(fname);
	if (!file) {
		std::cout << "Ошибка чтения файла" << std::endl;
		return -1;
	}

	std::cin >> fir >> sec >> msize;
	if (std::cin.fail()) {
		std::cout << "Ошибка чтения матрицы" << std::endl;
		return -1;
	}

	matrix.resize(msize, std::vector<RationalFraction>(msize));

	char simb;
	int el, prov;
	for (int i = 0; i < msize; ++i) {
		for (int j = 0; j < msize; ++j) {
			scanf_s("%d", &el);
			matrix[i][j].setNumerator(el);
			scanf_s("%c", &simb);
			if (simb == '/') {
				scanf_s("%d", &el);
				matrix[i][j].setDenominator(el);
			}
		}
	}

	return 1;
}
