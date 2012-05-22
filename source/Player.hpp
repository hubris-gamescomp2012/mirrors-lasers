#ifndef	PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject
{
public:
	Player(ResourceManager& a_ResMgr, cpSpace& a_Space);
	virtual void Update(float a_Dt);
	//
private:
	//
};

#endif	//PLAYER_HPP