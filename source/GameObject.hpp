#ifndef GAMEOBJ_HPP
#define GAMEOBJ_HPP

#include "ResourceManager.hpp"
#include <chipmunk\chipmunk.h>

class GameObject
{
public:
	GameObject(ResourceManager& a_ResMgr, cpSpace& a_Space);
	~GameObject();
	//
	SpriteID* GetSprite();
	virtual void Update(float a_Dt);
	//
	void SetPosition(float a_X, float a_Y);
protected:
	cpBody *m_pBody;
	cpShape *m_pShape;
	//
	ResourceManager& m_resMgr;
	SpriteID m_Sprite;
	//
};

#endif	//GAMEOBJ_HPP