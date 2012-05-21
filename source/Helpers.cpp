#include "Helpers.hpp"

#include <vector>
#include <sstream>

const char* GetRandomLetter(char** a_ppOut)
{
	char* out;
	switch(rand()%26)
	{
	case(0):
		{
			out = "A";
			break;
		}
	case(1):
		{
			out = "B";
			break;
		}
	case(2):
		{
			out = "C";
			break;
		}
	case(3):
		{
			out = "D";
			break;
		}
	case(4):
		{
			out = "E";
			break;
		}
	case(5):
		{
			out = "F";
			break;
		}
	case(6):
		{
			out = "G";
			break;
		}
	case(7):
		{
			out = "H";
			break;
		}
	case(8):
		{
			out = "I";
			break;
		}
	case(9):
		{
			out = "J";
			break;
		}
	case(10):
		{
			out = "K";
			break;
		}
	case(11):
		{
			out = "L";
			break;
		}
	case(12):
		{
			out = "M";
			break;
		}
	case(13):
		{
			out = "N";
			break;
		}
	case(14):
		{
			out = "O";
			break;
		}
	case(15):
		{
			out = "P";
			break;
		}
	case(16):
		{
			out = "Q";
			break;
		}
	case(17):
		{
			out = "R";
			break;
		}
	case(18):
		{
			out = "S";
			break;
		}
	case(19):
		{
			out = "T";
			break;
		}
	case(20):
		{
			out = "U";
			break;
		}
	case(21):
		{
			out = "V";
			break;
		}
	case(22):
		{
			out = "W";
			break;
		}
	case(23):
		{
			out = "X";
			break;
		}
	case(24):
		{
			out = "Y";
			break;
		}
	case(25):
		{
			out = "Z";
			break;
		}
	}
	if(a_ppOut)
		*a_ppOut = out;
	return out;
}

double max(double a_one, double a_two)
{
	if(a_one > a_two)
		return a_one;
	return a_two;
}

double min(double a_one, double a_two)
{
	if(a_one < a_two)
		return a_one;
	return a_two;
}

std::string Num2Str(double a_In)
{
	std::stringstream out;
	out << a_In;
	return out.str();
}

std::string Num2Str(float a_In)
{
	std::stringstream out;
	out << a_In;
	return out.str();
}

std::string Num2Str(int a_In)
{
	std::stringstream out;
	out << a_In;
	return out.str();
}

std::string Num2Str(short a_In)
{
	std::stringstream out;
	out << a_In;
	return out.str();
}

