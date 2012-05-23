#ifndef LASER_HPP
#define LASER_HPP

#include "GameObject.hpp"
#include <vector>

class Laser : public GameObject
{
public:
	Laser(ResourceManager& a_ResMgr, cpSpace& a_Space);
	virtual void Update(float a_Dt);
	//
private:
	//
};

#endif // LASER_HPP