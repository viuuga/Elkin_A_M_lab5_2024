/*
Елькин Александр Михайлович ИВТ-11БО 2024


Реализованно задание 1

*/


//


#include"NumPy.h" 


// Определитель методом гауса
bool gaus_determinant(std::vector<std::vector<RationalFraction>> matrix, RationalFraction& opr)
{
	RationalFraction mnojitel_for_opr(1, 1);
	int  n = matrix.size();


	for (int i = 0; i < n - 1; i++) {
		if (matrix[i][i].getNumerator() == 0) { // Если = 0 то переставляем дальше

			for (int j = i + 1; j < n; j++) {
				if (matrix[j][i].getNumerator() != 0) {

					matrix[i].swap(matrix[j]);
					mnojitel_for_opr *= -1;

					break;
				}
			}
		}

		if (matrix[i][i].getNumerator() != 0) {  //иначе домнажаем, вычитаем
			for (int j = i + 1; j < n; j++) {
				std::vector<RationalFraction> i_z(n);
				RationalFraction mnojitel(1, 1);
				i_z = matrix[i];   //отдельно сделал i-ю строку так как её вычитаем, она на определитель не влияет
				if (matrix[j][i].getNumerator() != 0) {
					mnojitel = matrix[j][i] / matrix[i][i]; // ищем нужные множители
					
					
					for (int x = 0; x < n; x++) {
						i_z[x] *= mnojitel;
						matrix[j][x] -= i_z[x];
						matrix[j][x].reduce();
						if (matrix[j][x].getNumerator() >= 1e9 || matrix[j][x].getDenominator() >= 1e9)
							return 1; // если хоть какаета часть числа начинает превышать 1е9 то завершаем метод гауса
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		opr *= matrix[i][i];  // Считаем главную диагональ
	}
	opr = opr / mnojitel_for_opr; // не забываем про вынесенные множители
	return 0;
}

// проверяет коллинеарность векторов (для фср)
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









// ищет строки-столбцы с наибольшим колличевством нулей
std::pair<int, int> poisk_0(std::vector<std::vector<RationalFraction>>& m, int n)
{
	int i, j, max_nul_strok = 0, count, num_str = 0, max_nul_stolb = 0, num_stolb = 0;
	std::pair<int, int> opr_line; //испульзую пейр так как 2-е значение - строка или столбец, 1-е - номер
	for (i = 0; i < n; i++) {
		count = 0;
		for (j = 0; j < n; j++) {
			if (m[i][j].getNumerator() == 0) {
				count++; // считаю нули
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
	}                                                 // присвоение значения где наиб кол-во нулей
	else {
		opr_line.first = num_stolb;
		opr_line.second = 2;
	}
	return opr_line;
}
//функция для нахождения определителя методом лапласа (из лабориторной №2)
RationalFraction laplas_determinant(std::vector<std::vector<RationalFraction>>& m, int n)
{
	if (n == 2) {    // условие выхода из рекурсии
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}
	int i, j, x, y;
	RationalFraction sum, elem;

	std::vector<std::vector<RationalFraction>> M(n - 1, std::vector<RationalFraction>(n - 1));
	std::pair<int, int> key;
	key = poisk_0(m, n);
	if (key.second == 2) { // проверяем по чему раскладывать (строка или столбец)
		sum = 0;
		j = key.first;
		for (i = 0; i < n; i++) {
			//создаем доп минор
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

			if (m[i][j].getNumerator() != 0) { // если ноль то смысла нет считать, тратить время.
				elem = m[i][j] * laplas_determinant(M, n - 1); // вход в рекурсию, поиск определитля доп минора.
				if ((i + j) % 2 == 0) {  //Проверка на знак
					sum += elem;
				}
				else {
					sum -= elem;
				}
			}
		}
	}
	else if (key.second == 1) { // проверяем по чему раскладывать (строка или столбец)
		sum = 0;
		i = key.first;
		for (j = 0; j < n; j++) {
			//создаем доп минор
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
			if (m[i][j].getNumerator() != 0) { // если ноль то смысла нет считать, тратить время.
				elem = m[i][j] * laplas_determinant(M, n - 1); // вход в рекурсию, поиск определитля доп минора.
				if ((i + j) % 2 == 0) { //Проверка на знак
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
	
	if (gaus_determinant(matrix, opr)) { // считаем методом гауса, если находит не точно то пересчитываем методом лапласа
		opr = laplas_determinant(matrix, matrix.size());
	}

	return opr;
}


