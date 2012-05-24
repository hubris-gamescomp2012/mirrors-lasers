#include <SFML/Graphics/Sprite.hpp>
#include "Animator.hpp"
#include "ResourceManager.hpp"

Animator::Animator(SpriteID& a_sprite, int a_width, int a_height, int a_rows, int a_columns, int a_framerate, int a_frames)
:	m_width(a_width)
,	m_height(a_height)
,	m_rows(a_rows)
,	m_columns(a_columns)
,	m_framerate(1.0f/a_framerate)
,	m_frames(a_frames)
,	m_timer(0.0f)
,	m_sprite(a_sprite)
,	m_currentFrame(0)
{
	sf::IntRect textRect(0, 0, m_width, m_height);
	m_sprite.sprite->setTextureRect(textRect);
}

void Animator::Update(float a_dt) {
	m_timer += a_dt;
	if (m_timer > m_framerate) {
		sf::IntRect textRect((m_currentFrame%m_columns)*m_width,
							 (m_currentFrame%m_rows)*m_height, 
							 m_width, 
							 m_height);

		m_sprite.sprite->setTextureRect(textRect);
		m_timer -= m_framerate;
		++m_currentFrame;
		if (m_currentFrame > m_frames) m_currentFrame = 0;
	}
}