#ifndef GAMEOBJ_HPP
#define GAMEOBJ_HPP

#include "ResourceManager.hpp"
#include <chipmunk\chipmunk.h>

class InputHandler;

class GameObject
{
public:
	GameObject(ResourceManager& a_ResMgr, cpSpace& a_Space);
	virtual ~GameObject();
	enum Type
	{
		INVALID = 0,
		//
		BLOCK,
		PLAYER,
		EMITTER,
		CATCHER,
		CURSOR,
		LASER,
		MIRROR,
		//
		MAX
	};
	Type GetType();
	//
	SpriteID* GetSprite();
	virtual void Update(float a_Dt);
	//
	virtual void SetPosition(float a_X, float a_Y);
	virtual void SetPosition(sf::Vector2f a_NewPos);
	virtual void SetPositionCenter(sf::Vector2f a_NewPos);
	virtual void SetPositionCenter(float a_X, float a_Y);
	virtual sf::Vector2f GetPosition();
	//
	void SetInputHandler(InputHandler* a_pInputHandler);
	InputHandler* GetInputHandler();
	//
	void Hide();
	void Show();
	//
protected:
	cpBody *m_pBody;
	cpShape *m_pShape;
	Type MyType;
	//
	ResourceManager& m_resMgr;
	SpriteID m_Sprite;
	//
	InputHandler* m_pInputHandler;

private:
	GameObject(const GameObject &);
	GameObject &operator=(const GameObject &);
};

#endif	//GAMEOBJ_HPP