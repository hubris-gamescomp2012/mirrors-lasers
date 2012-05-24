#include "Player.hpp"
#include <iostream>

#include "InputHandler.hpp"
#include "Helpers.hpp"
#include "Defs.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

Player::Player(ResourceManager& a_ResMgr, cpSpace& a_Space)
:	GameObject(a_ResMgr, a_Space)
,	m_OnGround(false)
,	RedirectAngle(0)
,	m_RedirectDir(0,0)
{
	MyType = PLAYER;
	//create a sprite
	m_resMgr.CreateSprite("media/player_body_64x64.png", &m_Sprite);

	//create the physbody
	sf::Vector2u sprSize = m_Sprite.sprite->getTexture()->getSize();
	cpFloat radius = sprSize.x/2;
	cpFloat mass = 1;

	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle(mass, radius, 0, cpv(0,0));

	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	m_pBody = cpSpaceAddBody(&a_Space, cpBodyNew(mass, moment));
	m_pBody->data = this;
	cpBodySetPos(m_pBody, cpv(500, 500));

	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	m_pShape = cpSpaceAddShape(&a_Space, cpCircleShapeNew(m_pBody, radius, cpv(0,0)));
	cpShapeSetFriction(m_pShape, 0);
	m_pShape->data = this;

	cpShapeSetCollisionType(m_pShape, COLLIDABLE::PLAYER);
}

void Player::Update(float a_Dt)
{
	GameObject::Update(a_Dt);
	//
	if(m_pInputHandler)
	{
		//horizontal movement
		if(m_pInputHandler->GetKeyDown(sf::Keyboard::Left))
		{
			//move left
			if(m_pBody->v.x > -250)
				cpBodyApplyImpulse(m_pBody, cpv(-320*a_Dt,0), cpv(0,0));
		}
		else if(m_pInputHandler->GetKeyDown(sf::Keyboard::Right))
		{
			//move right
			if(m_pBody->v.x < 250)
				cpBodyApplyImpulse(m_pBody, cpv(320*a_Dt,0), cpv(0,0));
		}
		else
		{
			m_pBody->v.x *= 0.9;
		}

		//jumping
		if(m_pInputHandler->GetKeyDown(sf::Keyboard::Space))
		{
			if(m_OnGround)
			{
				cpBodyApplyImpulse(m_pBody, cpv(0,-400), cpv(0,0));
				m_OnGround = false;
			}
		}

		//handle the cursor aiming
	}
}

void Player::SetOnGround()
{
	m_OnGround = true;
}

float Player::GetRedirectAngle()
{
	return RedirectAngle;
}

sf::Vector2f Player::GetRedirectDir()
{
	if(m_pInputHandler)
	{
		sf::Vector2f mousePos = m_pInputHandler->GetMousePos();
		m_RedirectDir = VectorNormalise(m_pInputHandler->GetMousePos() - GetPosition());
	}
	return m_RedirectDir;
}

void Player::SetRedirectDir(sf::Vector2f a_NewDir)
{
	m_RedirectDir = a_NewDir;
}
