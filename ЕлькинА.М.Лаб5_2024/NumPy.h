#pragma once

#include"stdafx.h"
#include"InOutPut.h"

#ifndef NUMPY_H
#define NUMPY_H

RationalFraction determinant(std::vector<std::vector<RationalFraction>>&);

std::vector<std::vector<RationalFraction>> FSR_Matrix(std::vector<std::vector<RationalFraction>>&, std::vector<std::pair<RationalFraction, int>>&);

#endif