#include "Cursor.hpp"

#include "InputHandler.hpp"

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>

Cursor::Cursor(ResourceManager& a_ResMgr, cpSpace& a_Space)
:	GameObject(a_ResMgr, a_Space)
{
	//create a sprite
	m_resMgr.CreateSprite("media/cursor.png", &m_Sprite);
}

void Cursor::Update(float a_Dt)
{
	GameObject::Update(a_Dt);
	//
	if(m_pInputHandler)
	{
		sf::Vector2f mousePos = m_pInputHandler->GetMousePos();
		m_Sprite.sprite->setPosition(mousePos.x, mousePos.y);
	}
}
