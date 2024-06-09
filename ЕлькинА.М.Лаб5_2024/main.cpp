/*
Елькин Александр Михайлович ИВТ-11БО 2024


Реализованно задание 1

*/



// основной фаил

#include "polynomial.h"


int input_mat(char name[256]) {
	RationalFraction opr;
	std::vector<std::pair<RationalFraction, int>> roots;
	int prov;

	std::vector<RationalFraction> polinomial;
	std::vector<std::vector<RationalFraction>> matrix;

	prov = input_rat_mat_file(matrix, name); // вводим матрицу

	if (prov < 0) {
		return prov;
	}
	
	std::cout << " n = " << matrix.size() << std::endl;
	output_rat_mat(matrix);

	polinomial = pol_from_mat(matrix); // находим характерестический многочлен (polinomial.cpp)
	output_polynomial(polinomial);
	roots = polynomial_roots(polinomial); // находим его корни (polinomial.cpp)
	output_pol_roots(roots);
	

	return 1;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	if (argc == 1) {
		std::cout << "Enter the file name: ";
		char name[256];
		std::cin >> name;
		input_mat(name);
	}
	else if (argc == 2) {
		int prov;
		prov = input_mat(argv[1]);
		if (prov == -1)
			std::cout << "Input error.";
		if (prov == -2) {
			std::cout << "File reading error";
		}
	}
	else {
		std::cout << "Error entering arguments";
	}
}
