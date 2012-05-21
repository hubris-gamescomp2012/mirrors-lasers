#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>

const char* GetRandomLetter(char** a_ppOut = NULL);

double max(double a_one, double a_two);
double min(double a_one, double a_two);

std::string Num2Str(double a_In);
std::string Num2Str(float a_In);
std::string Num2Str(int a_In);
std::string Num2Str(short a_In);

#endif	//HELPERS_HPP