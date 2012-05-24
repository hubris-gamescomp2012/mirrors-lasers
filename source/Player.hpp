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
	void SetRedirectDir(sf::Vector2f a_NewDir);
	sf::Vector2f GetRedirectDir();
	void SetOnGround();
	//
private:
	bool m_OnGround;
	float RedirectAngle;
	sf::Vector2f m_RedirectDir;
	//
};

#endif	//PLAYER_HPP