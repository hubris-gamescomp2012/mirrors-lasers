#include "Player.hpp"
#include "Mirror.hpp"

#include "InputHandler.hpp"
#include "Helpers.hpp"
#include "Defs.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

Player::Player(ResourceManager& a_ResMgr, cpSpace& a_Space)
:	GameObject(a_ResMgr, a_Space)
,	m_OnGround(false)
,	RedirectAngle(0)
,	m_RedirectDir(0,0)
,	m_pMirror(NULL)
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

	//create the mirror
	m_pMirror = new Mirror(a_ResMgr, a_Space);

	//create some spare mirrors
	for(short i=0;i<3;i++)
	{
		SpareMirrors.push_back(floatingMirror());
		m_resMgr.CreateSprite("media/mirror.png", &SpareMirrors.back().sprite);
		//
		float randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
		float randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
		SpareMirrors.back().sprite.sprite->setPosition(float(m_pBody->p.x) + randX, float(m_pBody->p.y) + randY);
		//
		m_resMgr.AddDrawableSprite(&SpareMirrors.back().sprite);
	}
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
	}

	//update the mirror position
	for(auto it = SpareMirrors.begin(); it != SpareMirrors.end(); it++)
	{
		//get the distance this mirror is from the player
		sf::Vector2f playerCenter = sf::Vector2f( float(m_pBody->p.x), float(m_pBody->p.y) );
		float dist = VectorMagnitude(playerCenter - it->sprite.sprite->getPosition());

		//if it's too far away, make it move a little
		if(dist > 32)
		{
			//speed up
			it->velocity += 100 * a_Dt;
		}
		else if(it->velocity > 0)
		{
			//slow down
			//it->velocity -= it->velocity * 0.9 * a_Dt;
			it->velocity = 0;
		}
		else
		{
			it->velocity = 0;
		}

		//move it in the direction of the player
		sf::Vector2f moveDir = VectorNormalise(playerCenter - it->sprite.sprite->getPosition());
		sf::Vector2f sprPos = it->sprite.sprite->getPosition();
		it->sprite.sprite->setPosition(sprPos + moveDir * it->velocity);
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

void Player::SetPosition(float a_X, float a_Y)
{
	//call parent function
	GameObject::SetPosition(a_X, a_Y);

	//move the spare mirrors
	for(auto it = SpareMirrors.begin(); it != SpareMirrors.end(); it++)
	{
		float randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
		float randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
		it->sprite.sprite->setPosition(float(m_pBody->p.x) + randX, float(m_pBody->p.y) + randY);
	}
}
