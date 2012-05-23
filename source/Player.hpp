#ifndef	PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject
{
public:
	Player(ResourceManager& a_ResMgr, cpSpace& a_Space);
	virtual void Update(float a_Dt);
	//
	float GetRedirectAngle();
	void SetOnGround();
	//
private:
	bool m_OnGround;
	float RedirectAngle;
	//
};

#endif	//PLAYER_HPP