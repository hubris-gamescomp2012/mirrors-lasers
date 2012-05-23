#ifndef LASER_HPP
#define LASER_HPP

#include "GameObject.hpp"
#include <vector>

#define LASER_VELOCITY 1000.f
#define MAX_LASER_DIST 2000.f

class Laser : public GameObject
{
public:
	Laser(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos);
	~Laser();
	virtual void Update(float a_Dt);
	//
	Laser* GetNextSegment();
	Laser* GetPreviousSegment();
	//
	void Bounce();
	//
	sf::Vector2f FacingDir;
private:
	sf::Vector2f m_StartPos;
	sf::Vector2f m_EndPos;
	float m_CurLength;
	float m_MaxLength;
	//
	Laser* m_pPreviousSegment;
	Laser* m_pNextChainSegment;
	//
	cpSpace& m_Space;
	//
};

#endif // LASER_HPP