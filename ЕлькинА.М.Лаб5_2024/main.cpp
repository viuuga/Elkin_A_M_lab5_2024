/*
������ ��������� ���������� ���-11�� 2024


������������ ������� 1

*/



// �������� ����

#include "polynomial.h"


int input_mat(char name[256]) {
	RationalFraction opr;
	std::vector<std::pair<RationalFraction, int>> roots;
	int prov;

	std::vector<RationalFraction> polinomial;
	std::vector<std::vector<RationalFraction>> matrix;

	prov = input_rat_mat_file(matrix, name); // ������ �������

	if (prov < 0) {
		return prov;
	}
	
	std::cout << " n = " << matrix.size() << std::endl;
	output_rat_mat(matrix);

	polinomial = pol_from_mat(matrix); // ������� ������������������ ��������� (polinomial.cpp)
	output_polynomial(polinomial);
	roots = polynomial_roots(polinomial); // ������� ��� ����� (polinomial.cpp)
	output_pol_roots(roots);
	

	return 1;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	if (argc == 1) {
		std::cout << "������� ��� �����: ";
		char name[256];
		std::cin >> name;
		input_mat(name);
	}
	else if (argc == 2) {
		int prov;
		prov = input_mat(argv[1]);
		if (prov == -1)
			std::cout << "������ �����.";
		if (prov == -2) {
			std::cout << "������ ������ �����";
		}
	}
	else {
		std::cout << "������ ����� ����������";
	}
}