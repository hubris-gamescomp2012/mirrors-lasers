#ifndef	PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Mirror;

struct floatingMirror
{
	float velocity;
	SpriteID sprite;
};

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
	virtual void SetPosition(float a_X, float a_Y);
	//
private:
	bool m_OnGround;
	float RedirectAngle;
	sf::Vector2f m_RedirectDir;
	//
	Mirror* m_pMirror;
	floatingMirror SpareMirrorOne;
	floatingMirror SpareMirrorTwo;
	floatingMirror SpareMirrorThree;
	//
	void UpdateFloatingMirrors(float a_Dt);
	//
};

#endif	//PLAYER_HPP