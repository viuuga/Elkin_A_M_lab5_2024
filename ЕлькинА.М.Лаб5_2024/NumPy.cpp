/*
������ ��������� ���������� ���-11�� 2024


������������ ������� 1

*/


//


#include"NumPy.h" 


// ������������ ������� �����
bool gaus_determinant(std::vector<std::vector<RationalFraction>> matrix, RationalFraction& opr)
{
	RationalFraction mnojitel_for_opr(1, 1);
	int  n = matrix.size();


	for (int i = 0; i < n - 1; i++) {
		if (matrix[i][i].getNumerator() == 0) { // ���� = 0 �� ������������ ������

			for (int j = i + 1; j < n; j++) {
				if (matrix[j][i].getNumerator() != 0) {

					matrix[i].swap(matrix[j]);
					mnojitel_for_opr *= -1;

					break;
				}
			}
		}

		if (matrix[i][i].getNumerator() != 0) {  //����� ���������, ��������
			for (int j = i + 1; j < n; j++) {
				std::vector<RationalFraction> i_z(n);
				RationalFraction mnojitel(1, 1);
				i_z = matrix[i];   //�������� ������ i-� ������ ��� ��� � ��������, ��� �� ������������ �� ������
				if (matrix[j][i].getNumerator() != 0) {
					mnojitel = matrix[j][i] / matrix[i][i]; // ���� ������ ���������
					
					
					for (int x = 0; x < n; x++) {
						i_z[x] *= mnojitel;
						matrix[j][x] -= i_z[x];
						matrix[j][x].reduce();
						if (matrix[j][x].getNumerator() >= 1e9 || matrix[j][x].getDenominator() >= 1e9)
							return 1; // ���� ���� ������� ����� ����� �������� ��������� 1�9 �� ��������� ����� �����
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		opr *= matrix[i][i];  // ������� ������� ���������
	}
	opr = opr / mnojitel_for_opr; // �� �������� ��� ���������� ���������
	return 0;
}

// ��������� �������������� �������� (��� ���)
bool eql_colinearity(std::vector<RationalFraction>& a, std::vector<RationalFraction>& b) {

	RationalFraction coef(0, 0);
	int count = 0;

	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i].getNumerator() != 0 && b[i].getNumerator() != 0) {
			coef = a[i] / b[i];
			break;
		}
	}

	for (int i = 0; i < b.size(); ++i) {
		if (b[i].getNumerator() == 0) count++;
	}

	if (count == a.size()) return 1;
	count = 0;
	if (coef == RationalFraction(0, 0)) return 0;

	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] / b[i] == coef || (a[i] == 0 && b[i] == 0)) count++;
	}

	if (count == a.size()) return 1;
	return 0;
}









// ���� ������-������� � ���������� ������������� �����
std::pair<int, int> poisk_0(std::vector<std::vector<RationalFraction>>& m, int n)
{
	int i, j, max_nul_strok = 0, count, num_str = 0, max_nul_stolb = 0, num_stolb = 0;
	std::pair<int, int> opr_line; //��������� ���� ��� ��� 2-� �������� - ������ ��� �������, 1-� - �����
	for (i = 0; i < n; i++) {
		count = 0;
		for (j = 0; j < n; j++) {
			if (m[i][j].getNumerator() == 0) {
				count++; // ������ ����
			}
		}
		if (count > max_nul_strok) {
			max_nul_strok = count;
			num_str = i;
		}
	}

	for (j = 0; j < n; j++) {
		count = 0;
		for (i = 0; i < n; i++) {
			if (m[i][j] == 0) {
				count++;
			}
		}
		if (count > max_nul_stolb) {
			max_nul_stolb = count;
			num_stolb = j;
		}
	}
	if (max_nul_strok > max_nul_stolb) {
		opr_line.first = num_str;
		opr_line.second = 1;
	}                                                 // ���������� �������� ��� ���� ���-�� �����
	else {
		opr_line.first = num_stolb;
		opr_line.second = 2;
	}
	return opr_line;
}
//������� ��� ���������� ������������ ������� ������� (�� ������������ �2)
RationalFraction laplas_determinant(std::vector<std::vector<RationalFraction>>& m, int n)
{
	if (n == 2) {    // ������� ������ �� ��������
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}
	int i, j, x, y;
	RationalFraction sum, elem;

	std::vector<std::vector<RationalFraction>> M(n - 1, std::vector<RationalFraction>(n - 1));
	std::pair<int, int> key;
	key = poisk_0(m, n);
	if (key.second == 2) { // ��������� �� ���� ������������ (������ ��� �������)
		sum = 0;
		j = key.first;
		for (i = 0; i < n; i++) {
			//������� ��� �����
			for (x = 0; x < n; x++) {
				for (y = 0; y < n; y++) {
					if (x != i && y != j) {
						if (x > i && y < j)
							M[x - 1][y] = m[x][y];
						if (x < i && y > j)
							M[x][y - 1] = m[x][y];
						if (x > i && y > j)
							M[x - 1][y - 1] = m[x][y];
						if (x < i && y < j)
							M[x][y] = m[x][y];
					}
				}
			}

			if (m[i][j].getNumerator() != 0) { // ���� ���� �� ������ ��� �������, ������� �����.
				elem = m[i][j] * laplas_determinant(M, n - 1); // ���� � ��������, ����� ����������� ��� ������.
				if ((i + j) % 2 == 0) {  //�������� �� ����
					sum += elem;
				}
				else {
					sum -= elem;
				}
			}
		}
	}
	else if (key.second == 1) { // ��������� �� ���� ������������ (������ ��� �������)
		sum = 0;
		i = key.first;
		for (j = 0; j < n; j++) {
			//������� ��� �����
			for (x = 0; x < n; x++) {
				for (y = 0; y < n; y++) {
					if (x != i && y != j) {
						if (x > i && y < j)
							M[x - 1][y] = m[x][y];
						if (x < i && y > j)
							M[x][y - 1] = m[x][y];
						if (x > i && y > j)
							M[x - 1][y - 1] = m[x][y];
						if (x < i && y < j)
							M[x][y] = m[x][y];
					}
				}
			}
			if (m[i][j].getNumerator() != 0) { // ���� ���� �� ������ ��� �������, ������� �����.
				elem = m[i][j] * laplas_determinant(M, n - 1); // ���� � ��������, ����� ����������� ��� ������.
				if ((i + j) % 2 == 0) { //�������� �� ����
					sum += elem;
				}
				else {
					sum -= elem;
				}
			}
		}
	}
	return sum;
}


RationalFraction determinant(std::vector<std::vector<RationalFraction>>& matrix)
{
	RationalFraction opr(1, 1);
	
	if (gaus_determinant(matrix, opr)) { // ������� ������� �����, ���� ������� �� ����� �� ������������� ������� �������
		opr = laplas_determinant(matrix, matrix.size());
	}

	return opr;
}


