#ifndef EMITTER_HPP
#define EMITTER_HPP

#include "GameObject.hpp"
#include "Defs.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>

class Laser;
class Animator;

class Emitter : public GameObject
{
public:
	Emitter(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos);
	~Emitter();
	virtual void Update(float a_Dt);
	void ParseCatchers(std::vector<sf::Vector2f>& a_catcherPositions);
	bool GetWon();
	//
private:
	Laser* m_pStartLaser;
	cpSpace& m_Space;
	Animator* m_pAnimator;
	//
	StaticRigidQuad m_BoxBounds;
};

#endif	//EMITTER_HPP