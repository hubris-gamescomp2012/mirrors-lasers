#include "GameObject.hpp"
#include "Renderer.hpp"

#include "InputHandler.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

GameObject::GameObject(ResourceManager& a_ResMgr, cpSpace& a_Space)
:	m_resMgr(a_ResMgr)
,	m_pShape(NULL)
,	m_pBody(NULL)
,	MyType(INVALID)
,	m_pInputHandler(NULL)
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
	if(m_pBody && m_Sprite.sprite)
	{
		sf::Vector2u sprSize = m_Sprite.sprite->getTexture()->getSize();
		a_X += sprSize.x/2;
		a_Y += sprSize.y/2;
		m_pBody->p.x = a_X;
		m_pBody->p.y = a_Y;
		m_Sprite.sprite->setPosition(a_X, a_Y);
	}
	else if(m_Sprite.sprite)
	{
		m_Sprite.sprite->setPosition(a_X, a_Y);
	}
}

void GameObject::SetPosition(sf::Vector2f a_NewPos)
{
	SetPosition(a_NewPos.x, a_NewPos.y);
}

void GameObject::SetPositionCenter(float a_X, float a_Y)
{
	sf::Vector2u sprSize = m_Sprite.sprite->getTexture()->getSize();
	SetPosition(a_X - sprSize.x/2, a_Y - sprSize.y/2);
}

void GameObject::SetPositionCenter(sf::Vector2f a_NewPos)
{
	SetPositionCenter(a_NewPos.x, a_NewPos.y);
}

void GameObject::Update(float a_Dt)
{
	if(m_pBody && m_Sprite.sprite)
	{
		sf::Vector2u sprSize = m_Sprite.sprite->getTexture()->getSize();
		m_Sprite.sprite->setPosition(float(m_pBody->p.x) - sprSize.x / 2, float(m_pBody->p.y) - sprSize.y / 2);
	}
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

GameObject::Type GameObject::GetType()
{
	return MyType;
}

sf::Vector2f GameObject::GetPosition()
{
	sf::Vector2f out(0,0);
	if(m_Sprite.sprite)
		out = m_Sprite.sprite->getPosition();
	return out;
}
