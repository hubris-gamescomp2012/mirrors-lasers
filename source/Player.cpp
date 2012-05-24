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
	//
	m_resMgr.CreateSprite("media/mirror1.png", &SpareMirrorOne.sprite);
	float randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	float randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	SpareMirrorOne.sprite.sprite->setPosition(m_Sprite.sprite->getPosition() + sf::Vector2f(randX, randY));
	//m_resMgr.AddDrawableSprite(&SpareMirrorOne.sprite);
	//
	m_resMgr.CreateSprite("media/mirror1.png", &SpareMirrorTwo.sprite);
	randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	SpareMirrorTwo.sprite.sprite->setPosition(m_Sprite.sprite->getPosition() + sf::Vector2f(randX, randY));
	//m_resMgr.AddDrawableSprite(&SpareMirrorTwo.sprite);
	//
	m_resMgr.CreateSprite("media/mirror1.png", &SpareMirrorThree.sprite);
	randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	SpareMirrorThree.sprite.sprite->setPosition(m_Sprite.sprite->getPosition() + sf::Vector2f(randX, randY));
	//m_resMgr.AddDrawableSprite(&SpareMirrorThree.sprite);
}

void Player::UpdateFloatingMirrors(float a_Dt)
{
	//update the mirror position
	/*floatingMirror SpareMirrorOne;
	floatingMirror SpareMirrorTwo;
	floatingMirror SpareMirrorThree;*/
	/*
	{
		//get the distance this mirror is from the player
		sf::Vector2f playerCenter = sf::Vector2f( float(m_pBody->p.x), float(m_pBody->p.y) );
		float dist = VectorMagnitude(playerCenter - SpareMirrorOne.sprite.sprite->getPosition());

		//if it's too far away, make it move a little
		if(dist > 32)
		{
			//speed up
			SpareMirrorOne.velocity += 100 * a_Dt;
		}
		else if(SpareMirrorOne.velocity > 0)
		{
			//slow down
			//it->velocity -= it->velocity * 0.9 * a_Dt;
			SpareMirrorOne.velocity = 0;
		}
		else
		{
			SpareMirrorOne.velocity = 0;
		}

		//move it in the direction of the player
		sf::Vector2f moveDir = VectorNormalise(playerCenter - SpareMirrorOne.sprite.sprite->getPosition());
		sf::Vector2f sprPos = SpareMirrorOne.sprite.sprite->getPosition();
		SpareMirrorOne.sprite.sprite->setPosition(sprPos + moveDir * SpareMirrorOne.velocity);
	}

	{
		//get the distance this mirror is from the player
		sf::Vector2f playerCenter = sf::Vector2f( float(m_pBody->p.x), float(m_pBody->p.y) );
		float dist = VectorMagnitude(playerCenter - SpareMirrorTwo.sprite.sprite->getPosition());

		//if it's too far away, make it move a little
		if(dist > 32)
		{
			//speed up
			SpareMirrorTwo.velocity += 100 * a_Dt;
		}
		else if(SpareMirrorTwo.velocity > 0)
		{
			//slow down
			//it->velocity -= it->velocity * 0.9 * a_Dt;
			SpareMirrorTwo.velocity = 0;
		}
		else
		{
			SpareMirrorTwo.velocity = 0;
		}

		//move it in the direction of the player
		sf::Vector2f moveDir = VectorNormalise(playerCenter - SpareMirrorTwo.sprite.sprite->getPosition());
		sf::Vector2f sprPos = SpareMirrorTwo.sprite.sprite->getPosition();
		SpareMirrorTwo.sprite.sprite->setPosition(sprPos + moveDir * SpareMirrorTwo.velocity);
	}

	{
		//get the distance this mirror is from the player
		sf::Vector2f playerCenter = sf::Vector2f( float(m_pBody->p.x), float(m_pBody->p.y) );
		float dist = VectorMagnitude(playerCenter - SpareMirrorThree.sprite.sprite->getPosition());

		//if it's too far away, make it move a little
		if(dist > 32)
		{
			//speed up
			SpareMirrorThree.velocity += 100 * a_Dt;
		}
		else if(SpareMirrorThree.velocity > 0)
		{
			//slow down
			//it->velocity -= it->velocity * 0.9 * a_Dt;
			SpareMirrorThree.velocity = 0;
		}
		else
		{
			SpareMirrorThree.velocity = 0;
		}

		//move it in the direction of the player
		sf::Vector2f moveDir = VectorNormalise(playerCenter - SpareMirrorThree.sprite.sprite->getPosition());
		sf::Vector2f sprPos = SpareMirrorThree.sprite.sprite->getPosition();
		SpareMirrorThree.sprite.sprite->setPosition(sprPos + moveDir * SpareMirrorThree.velocity);
	}
	*/
	SpareMirrorOne.sprite.sprite->setPosition(m_Sprite.sprite->getPosition() + sf::Vector2f( float(rand())/RAND_MAX * 64.f - 32.f, float(rand())/RAND_MAX * 64.f - 16.f) );
	SpareMirrorTwo.sprite.sprite->setPosition(m_Sprite.sprite->getPosition() + sf::Vector2f( float(rand())/RAND_MAX * 64.f - 32.f, float(rand())/RAND_MAX * 64.f - 16.f) );
	SpareMirrorThree.sprite.sprite->setPosition(m_Sprite.sprite->getPosition() + sf::Vector2f( float(rand())/RAND_MAX * 64.f - 32.f, float(rand())/RAND_MAX * 64.f - 16.f) );
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

	//update floating mirrors
	UpdateFloatingMirrors(a_Dt);

	//update current mirror
	sf::Vector2f curPos = m_Sprite.sprite->getPosition();
	sf::Vector2u sprSize = m_pMirror->GetSprite()->sprite->getTexture()->getSize();
	curPos.y += 16.f + sprSize.y / 2;
	curPos.x += sprSize.x / 2;
	m_pMirror->SetPosition(curPos);
	m_pMirror->SetRotationAngle(GetAngleFromDir( VectorNormalise(m_pInputHandler->GetMousePos() - curPos) ));
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

	m_pMirror->SetPosition(a_X, a_Y);

	//move the spare mirrors
	float randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	float randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	SpareMirrorOne.sprite.sprite->setPosition(float(m_pBody->p.x) + 0, float(m_pBody->p.y) + 0);
	//
	randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	SpareMirrorTwo.sprite.sprite->setPosition(float(m_pBody->p.x) + 0, float(m_pBody->p.y) + 0);
	//
	randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	SpareMirrorThree.sprite.sprite->setPosition(float(m_pBody->p.x) + 0, float(m_pBody->p.y) + 0);
}
