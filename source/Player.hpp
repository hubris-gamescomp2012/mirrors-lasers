#ifndef	PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Mirror;

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
	Mirror* GetMirror();
	//
private:
	bool m_OnGround;
	float RedirectAngle;
	sf::Vector2f m_RedirectDir;
	//
	Mirror* m_pMirror;
	//
};

#endif	//PLAYER_HPP