#ifndef MIRROR_HPP
#define MIRROR_HPP

#include "GameObject.hpp"

struct cpShape;
class Laser;
class Emitter;

class Mirror: public GameObject
{
public:
	Mirror(ResourceManager& a_ResMgr, cpSpace& a_Space);
	~Mirror();
	//
	virtual void Update(float a_Dt);
	//
	void SetRotationAngle(float a_Angle);	//radians
	float GetRotationAngle();
	void ParseEmitter(Emitter* a_emitter);
	bool GetWon();
	void ParseCatchers(std::vector<sf::Vector2f>& a_catcherPositions);
	void BlockLaser(sf::Vector2f a_blockPos);
	//
	virtual void SetPosition(sf::Vector2f a_NewPos);
	//
private:
	cpShape* m_pReflectLine;
	cpBody* m_pReflectBody;
	cpSpace& m_pSpace;
	Laser* m_pLaser;
	//
};

/*
cpFloat cpBodyGetAngle(const cpBody *body)
void cpBodySetAngle(cpBody *body, cpFloat a)
//rotation in radians
*/

#endif	//MIRROR_HPP