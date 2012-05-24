#include "Emitter.hpp"
#include <SFML\Graphics\Sprite.hpp>
#include "Laser.hpp"
#include "Animator.hpp"

Emitter::Emitter(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos)
:	GameObject(a_ResMgr, a_Space)
,	m_Space(a_Space)
,	m_pAnimator(NULL)
{
	m_resMgr.CreateSprite("media/Transmitter_on_32x32.png", &m_Sprite);
	m_pAnimator = new Animator(m_Sprite, 32, 32, 3, 8, 10, 24);
	m_Sprite.sprite->setPosition(a_StartPos);
	a_StartPos.y += 32;	//move it into the middle of the emitter
	a_StartPos.x += 32;	//move it in front of the emitter
	m_pStartLaser = new Laser(a_ResMgr, a_Space, a_StartPos);
	//m_pStartLaser->SetFacingDir(sf::Vector2f(1,1));
	m_pStartLaser->Show();
}

void Emitter::Update(float a_Dt)
{
	if(m_pAnimator)
		m_pAnimator->Update(a_Dt);

	if(m_pStartLaser)
		m_pStartLaser->Update(a_Dt);
}

Emitter::~Emitter() {
	if (m_pAnimator) delete m_pAnimator;
}
