#ifndef	PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Mirror;
class Emitter;

struct floatingMirror
{
	float velocity;
	SpriteID sprite;
};

class Player : public GameObject
{
public:
	Player(ResourceManager& a_ResMgr, cpSpace& a_Space);
	~Player();
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
	void ParseEmitter(Emitter* a_emitter);
	void ParseCatchers(std::vector<sf::Vector2f>& a_catcherPositions);
	bool GetWon();
	//
private:
	bool m_OnGround;
	float RedirectAngle;
	sf::Vector2f m_RedirectDir;
	cpSpace& m_Space;
	bool m_mousePressed;
	//
	Mirror* m_pMirror;
	Mirror* m_pMirror1;
	Mirror* m_pMirror2;
	Mirror* m_pMirror3;
	floatingMirror SpareMirrorOne;
	floatingMirror SpareMirrorTwo;
	floatingMirror SpareMirrorThree;
	int m_activeMirrors;
	//
	void UpdateFloatingMirrors(float a_Dt);
	//
};

#endif	//PLAYER_HPP