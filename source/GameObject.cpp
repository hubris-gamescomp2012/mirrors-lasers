#include "GameObject.hpp"
#include "Renderer.hpp"

#include "InputHandler.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

GameObject::GameObject(ResourceManager& a_ResMgr, cpSpace& a_Space)
:	m_resMgr(a_ResMgr)
,	m_pShape(NULL)
,	m_pBody(NULL)
,	MyType(INVALID)
{
	//not all game objects have physbodies
}

GameObject::~GameObject()
{
	m_resMgr.DeleteSprite(m_Sprite.ID);
	if(m_pBody)
		cpBodyFree(m_pBody);
	if(m_pShape)
		cpShapeFree(m_pShape);
}

SpriteID* GameObject::GetSprite()
{
	return &m_Sprite;
}

void GameObject::SetPosition(float a_X, float a_Y)
{
	if(m_pBody)
	{
		m_pBody->p.x = a_X;
		m_pBody->p.y = a_Y;
	}
	else if(m_Sprite.sprite)
	{
		m_Sprite.sprite->setPosition(a_X, a_Y);
	}
}

void GameObject::Update(float a_Dt)
{
	if(m_pBody)
		m_Sprite.sprite->setPosition(float(m_pBody->p.x), float(m_pBody->p.y));
}

void GameObject::SetInputHandler(InputHandler* a_pInputHandler)
{
	m_pInputHandler = a_pInputHandler;
}

InputHandler* GameObject::GetInputHandler()
{
	return m_pInputHandler;
}

void GameObject::Hide()
{
	m_resMgr.RemoveDrawableSprite(&m_Sprite);
}

void GameObject::Show()
{
	m_resMgr.AddDrawableSprite(&m_Sprite);
}
