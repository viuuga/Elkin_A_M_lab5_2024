#pragma once

#include"NumPy.h"

#ifndef POLYNOMIAL_h
#define POLYNOMIAL_h

std::vector<RationalFraction> pol_from_mat(std::vector<std::vector<RationalFraction>>& matrix);

std::vector<std::pair<RationalFraction, int>> polynomial_roots(std::vector<RationalFraction> polynommial);

#endif