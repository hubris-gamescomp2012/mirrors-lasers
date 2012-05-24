#ifndef EMITTER_HPP
#define EMITTER_HPP

#include "GameObject.hpp"
#include "Defs.hpp"

class Laser;

class Emitter : public GameObject
{
public:
	Emitter(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos);
	virtual void Update(float a_Dt);
	//
private:
	Laser* m_pStartLaser;
	cpSpace& m_Space;
	//
	StaticRigidQuad m_BoxBounds;
};

#endif	//EMITTER_HPP