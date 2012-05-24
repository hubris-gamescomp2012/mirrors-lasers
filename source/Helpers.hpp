#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <SFML\System\Vector2.hpp>

const char* GetRandomLetter(char** a_ppOut = NULL);

double max(double a_one, double a_two);
double min(double a_one, double a_two);

std::string Num2Str(double a_In);
std::string Num2Str(float a_In);
std::string Num2Str(int a_In);
std::string Num2Str(short a_In);

float GetAngleFromDir(sf::Vector2f a_StartPos, sf::Vector2f a_EndPos);
float GetAngleFromDir(sf::Vector2f a_Dir);

sf::Vector2f AngleToVector(float angle);

float VectorToAngle(sf::Vector2f vector);

float VectorMagnitude(sf::Vector2f a_Vec);

sf::Vector2f VectorNormalise(sf::Vector2f a_Vec);

#endif	//HELPERS_HPP