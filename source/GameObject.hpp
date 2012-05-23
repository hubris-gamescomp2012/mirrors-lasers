#ifndef GAMEOBJ_HPP
#define GAMEOBJ_HPP

#include "ResourceManager.hpp"
#include <chipmunk\chipmunk.h>

class InputHandler;

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
	//
	void SetInputHandler(InputHandler* a_pInputHandler);
	InputHandler* GetInputHandler();
	//
	enum Type
	{
		INVALID = 0,
		BLOCK,
		PLAYER,
		BOUNDARY,
		//
		MAX
	};
protected:
	cpBody *m_pBody;
	cpShape *m_pShape;
	Type MyType;
	//
	ResourceManager& m_resMgr;
	SpriteID m_Sprite;
	//
	InputHandler* m_pInputHandler;
};

#endif	//GAMEOBJ_HPP