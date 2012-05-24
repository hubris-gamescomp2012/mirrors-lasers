#ifndef MIRROR_HPP
#define MIRROR_HPP

#include "GameObject.hpp"

struct cpShape;

class Mirror: public GameObject
{
public:
	Mirror(ResourceManager& a_ResMgr, cpSpace& a_Space);
	~Mirror();
	//
	virtual void Update(float a_Dt);
	//
private:
	cpShape* m_pLineSegment;
	//
};

#endif	//MIRROR_HPP