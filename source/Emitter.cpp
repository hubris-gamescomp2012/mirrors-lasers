#include "Emitter.hpp"
#include <SFML\Graphics\Sprite.hpp>
#include "Laser.hpp"

Emitter::Emitter(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos)
:	GameObject(a_ResMgr, a_Space)
,	m_Space(a_Space)
{
	m_resMgr.CreateSprite("media/laser_emitter_32x64.png", &m_Sprite);
	m_Sprite.sprite->setPosition(a_StartPos);
	a_StartPos.y += 32;	//move it into the middle of the emitter
	a_StartPos.x += 32;	//move it in front of the emitter
	m_pStartLaser = new Laser(a_ResMgr, a_Space, a_StartPos);
	//m_pStartLaser->SetFacingDir(sf::Vector2f(1,1));
	m_pStartLaser->Show();
}

void Emitter::Update(float a_Dt)
{
	if(m_pStartLaser)
		m_pStartLaser->Update(a_Dt);
}
