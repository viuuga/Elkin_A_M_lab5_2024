/*
Елькин Александр Михайлович ИВТ-11БО 2024


Реализованно задание 1

*/


// фаил для функций связанных с многочленом

#include "polynomial.h"



//для подсчёта суммы главных миноров нахлдим определитель со столбцами и строками соответствующими переданной перестановкой
RationalFraction vich_mn(std::vector<std::vector<RationalFraction>>& matrix, std::vector<int>& perestan) {

    int n = perestan.size();
    std::vector<std::vector<RationalFraction>> buff_matrix(n, std::vector<RationalFraction>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            buff_matrix[i][j] = matrix[perestan[i] - 1][perestan[j] - 1];// создаём матрицу с нужными элемениами
        }
    }
    return determinant(buff_matrix); //возвращаем её определитель
}


// номера для главных миноров находим при помощи перестановок сочетаний
void perestan_sochit(std::vector<std::vector<RationalFraction>>& matrix, int M, int N, RationalFraction &mnoj) {
    std::vector<int> numbers(M);
    for (int i = 0; i < N; ++i) {
        numbers[i] = 1;
    }

    
    std::vector<int> combination;
    for (int i = 0; i < M; ++i) {
        if (numbers[i] == 1) {
            combination.push_back(i + 1);
        }
    }
    mnoj += vich_mn(matrix, combination);
    while (std::prev_permutation(numbers.begin(), numbers.end())) {
        std::vector<int> combination1;
        for (int i = 0; i < M; ++i) {
            if (numbers[i] == 1) {
                combination1.push_back(i + 1);
            }
        }
        mnoj += vich_mn(matrix, combination1);
    }

}


// обновляет вектор корней
void update_roots(std::vector<std::pair<RationalFraction, int>>& roots, RationalFraction root) {
    bool in = false;
    int num;
    for (int i = 0; i < roots.size(); ++i) {
        if (root == roots[i].first) {
            in = true;
            num = i;
            break;
        }
    }
    
    if (in) {
        roots[num].second += 1;
    }
    else roots.push_back({ root, 1 });
}



// проверяем является ли число корнем многочлена
bool vichis_rats_roots(RationalFraction root, std::vector<RationalFraction>& polynom) {
    RationalFraction sum(0, 1);
    int deg = polynom.size();

    for (int i = 1; i <= deg; ++i) {
        sum += (root ^ (deg - i)) * polynom[i - 1];
    }

    if (sum.getNumerator() == 0) return 1;
    else return 0;
}


// деление многочлена
std::vector<RationalFraction> delenie_pol(std::vector<RationalFraction> delimoe, std::vector<RationalFraction> delitel) {
    std::vector<RationalFraction> chastnoe;

    while (delimoe.size() >= delitel.size()) {
        RationalFraction coef = delimoe[0] / delitel[0];
        chastnoe.push_back(coef);

        for (int i = 0; i < delitel.size(); ++i) {
            delimoe[i] -= coef * delitel[i];
        }
        delimoe.erase(delimoe.begin());
    }

    return chastnoe;
}


//Если многочлен имеет рациональные множители, то избавляемся от них
long long NOK(std::vector<long long> m) {
    long long max_el = -1e18, buff, count_break = 0;
    for (long long i : m) {
        if (i > max_el) max_el = i;
    }
    buff = max_el;

    bool flag = true;
    while (flag) {
        flag = false;
        for (long long i : m) {
            if (max_el % i != 0) {
                flag = true;
                break;
            }
        }
        if (++count_break == 100000)
            return -1e18;
        if (flag == true)
            max_el += buff;
    }
    return max_el;
}

// обираем повторения
void overlap(std::vector<RationalFraction> &vec) {

    for (int i = 0; i < vec.size()-1; ++i) {
        for (int j = i + 1; j < vec.size(); ++j) {
            if (i < vec.size() && j < vec.size() && vec[i] == vec[j]) {
                vec.erase(vec.begin() + j);
            }

        }
    }

}




// находим характеристический многочлен
std::vector<RationalFraction> pol_from_mat(std::vector<std::vector<RationalFraction>>& matrix)
{
    int N = matrix.size();
    std::vector<RationalFraction> polinomial(N+1);
    RationalFraction rf(1, 1);


    if (N % 2 == 0) {
        polinomial[0] = rf;
    }
    else polinomial[0] = -rf;

    for (int det_size = 1; det_size <= N; ++det_size) {// ноходим множители
        RationalFraction mnoj(0, 1);

        perestan_sochit(matrix, N, det_size, mnoj);// перебираем все главные миноры заданного размера
        
        if ((N - det_size) % 2 != 0) mnoj *= -1;

        mnoj.reduce();
        polinomial[det_size] = mnoj;
    }
   



    return polinomial;
}



// находим корни многочлена
std::vector<std::pair<RationalFraction, int>> polynomial_roots(std::vector<RationalFraction> polynommial)
{
    int max_roots = polynommial.size() - 1, kol_root = 0;
    std::vector<std::pair<RationalFraction, int>> roots;
    bool flag = true;

    std::vector<long long> znam;
    for (RationalFraction el : polynommial)
        if (el.getDenominator() != 1) znam.push_back(el.getDenominator());

    if (znam.size() > 0) { // убираем дроби
        long long nok = NOK(znam);

        if (nok == -1e18) return {};

        for (int i = 0; i < polynommial.size(); ++i) {
            polynommial[i] = polynommial[i] * nok;
        }
    }

    while (flag)
    {
        flag = false;
        while (polynommial.size() > 0 && polynommial[polynommial.size()-1].getNumerator() == 0) { // проверяем корни равные 0
            update_roots(roots, RationalFraction(0, 1));
            polynommial.pop_back();
            kol_root++;
        }
        if (kol_root == max_roots) break;
        RationalFraction cv_chlen = polynommial[polynommial.size()-1], naib_chlen = polynommial[0];
        std::vector<int> vse_p, vse_q;


        // 219 - 238 находи все делители свободных членов
        cv_chlen.reduce(); naib_chlen.reduce();
        if (cv_chlen.getDenominator() != 1 || naib_chlen.getDenominator() != 1) break;

        for (int i = 1; i < abs(cv_chlen.getNumerator()) / 2 + 1; ++i) {
            if (cv_chlen.getNumerator() % i == 0) {
                vse_p.push_back(i); vse_p.push_back(-i);
            }
        }
        if (abs(cv_chlen.getNumerator()) > 2);
            vse_p.push_back(cv_chlen.getNumerator()); vse_p.push_back(-cv_chlen.getNumerator());

        for (int i = 1; i < abs(naib_chlen.getNumerator()) / 2 + 1; ++i) {
            if (naib_chlen.getNumerator() % i == 0) {
                vse_q.push_back(i);
            }
        }
        if (abs(naib_chlen.getNumerator()) > 2);
            vse_q.push_back(naib_chlen.getNumerator());
 


        // ищем корни
        for (int p : vse_p) {
            for (int q : vse_q) {
                RationalFraction rt(p, q);
                if (vichis_rats_roots(rt, polynommial)) {
                    update_roots(roots, rt);
                    kol_root++;
                    polynommial = delenie_pol(polynommial, { 1, -rt });
                    flag = true;
                }
            }
        }


        if (kol_root == max_roots) break;
    }

    return roots;
}



