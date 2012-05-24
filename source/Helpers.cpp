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

float GetAngleFromDir(sf::Vector2f a_StartPos, sf::Vector2f a_EndPos)
{
	sf::Vector2f diff = a_StartPos - a_EndPos;
	diff /= sqrtf(diff.x * diff.x + diff.y * diff.y);

	float rad = atan2f(diff.y, diff.x);

	rad += 3.14159f * 0.5f;

	return rad;
}

float GetAngleFromDir(sf::Vector2f a_Dir)
{
	a_Dir /= sqrtf(a_Dir.x * a_Dir.x + a_Dir.y * a_Dir.y);

	float rad = atan2f(a_Dir.y, a_Dir.x);
	//
	return rad;

	rad += 3.14159f * 0.5f;
	//
	return rad;
}

float GetVectorMagnitude(sf::Vector2f a_Vec)
{
	return sqrtf(a_Vec.x * a_Vec.x + a_Vec.y * a_Vec.y);
}

//takes rad
sf::Vector2f AngleToVector(float angle)
{
    return sf::Vector2f((float)sinf(angle), (float)sinf(angle));
}

//returns degree
float VectorToAngle(sf::Vector2f vector)
{
	float rad = (float)atan2f(vector.y, vector.x);
    return 180 * rad / 3.14159265f;
}

//2pi rad = 360
//1 rad = 180/pi
//x rad = 180x/pi