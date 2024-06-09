#pragma once
#include"rational.h"
#include<vector>
#include<fstream>
#include<iostream>


#ifndef INOUTPUT_h
#define INOUTPUT_h

void output_rat_mat(std::vector<std::vector<RationalFraction>>&);

void output_int_mat(std::vector<std::vector<int>>&);

void output_polynomial(std::vector<RationalFraction>& pol);

void output_pol_roots(std::vector<std::pair<RationalFraction, int>>&);

int input_rat_mat_file(std::vector<std::vector<RationalFraction>>&, char fname[256]);


#endif

