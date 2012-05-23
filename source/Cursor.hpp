#ifndef CURSOR_HPP
#define CURSOR_HPP

#include "GameObject.hpp"

class Cursor : public GameObject
{
public:
	Cursor(ResourceManager& a_ResMgr, cpSpace& a_Space);
	virtual void Update(float a_Dt);
	//
private:
	//
};

#endif	//CURSOR_HPP