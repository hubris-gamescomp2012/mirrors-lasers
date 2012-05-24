#ifndef EMITTER_HPP
#define EMITTER_HPP

#include "GameObject.hpp"

class Laser;
class Animator;

class Emitter : public GameObject
{
public:
	Emitter(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos);
	~Emitter();
	virtual void Update(float a_Dt);
	//
private:
	Laser* m_pStartLaser;
	cpSpace& m_Space;
	Animator* m_pAnimator;
	//
};

#endif	//EMITTER_HPP