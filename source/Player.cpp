#include "Player.hpp"
#include <iostream>

Player::Player(ResourceManager& a_ResMgr, cpSpace& a_Space)
:	GameObject(a_ResMgr, a_Space)
{
	//create a sprite
	m_resMgr.CreateSprite("media/player.png", &m_Sprite);
}

void Player::Update(float a_Dt)
{
	GameObject::Update(a_Dt);
	//
	//std::cout << "Player: " << m_pBody->p.x << "x, " << m_pBody->p.y << "y" << std::endl;
}
