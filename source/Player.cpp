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
,	m_activeMirrors(0)
,	m_Space(a_Space)
,	m_pMirror1(NULL)
,	m_pMirror2(NULL)
,	m_pMirror3(NULL)
,   m_mousePressed(false)
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

	cpShapeSetCollisionType(m_pShape, PLAYER);
	cpShapeSetLayers(m_pShape, (cpLayers)PLAYER);

	//create the mirror
	m_pMirror = new Mirror(a_ResMgr, a_Space);

	//create some spare mirrors
	//
	m_resMgr.CreateSprite("media/player_body_64x64.png", &SpareMirrorOne.sprite);
	float randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	float randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	SpareMirrorOne.sprite.sprite->setPosition(m_Sprite.sprite->getPosition() + sf::Vector2f(randX, randY));
	//m_resMgr.AddDrawableSprite(&SpareMirrorOne.sprite);
	//
	m_resMgr.CreateSprite("media/player_body_64x64.png", &SpareMirrorTwo.sprite);
	randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	SpareMirrorTwo.sprite.sprite->setPosition(m_Sprite.sprite->getPosition() + sf::Vector2f(randX, randY));
	//m_resMgr.AddDrawableSprite(&SpareMirrorTwo.sprite);
	//
	m_resMgr.CreateSprite("media/player_body_64x64.png", &SpareMirrorThree.sprite);
	randX = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	randY = (float(rand()) / (RAND_MAX / 2) - 1) * 64.f;
	SpareMirrorThree.sprite.sprite->setPosition(m_Sprite.sprite->getPosition() + sf::Vector2f(randX, randY));
	//m_resMgr.AddDrawableSprite(&SpareMirrorThree.sprite);
}

Player::~Player() {
	if (m_activeMirrors > 0) {
		m_pMirror1->Hide();
		delete m_pMirror1;
		m_pMirror1 = NULL;
	}

	if (m_activeMirrors > 1) {
		m_pMirror2->Hide();
		delete m_pMirror2;
		m_pMirror2 = NULL;
	}

	if (m_activeMirrors > 2) {
		m_pMirror3->Hide();
		delete m_pMirror3;
		m_pMirror3 = NULL;
	}

	if (m_pMirror) {
		m_pMirror->Hide();
		delete m_pMirror;
		m_pMirror = NULL;
	}
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

bool Player::GetWon() {
	bool won = false;
	if (!won) won = m_pMirror->GetWon();
	if (!won && m_pMirror1) won = m_pMirror1->GetWon();
	if (!won && m_pMirror2) won = m_pMirror2->GetWon();
	if (!won && m_pMirror3) won = m_pMirror3->GetWon();
	return won;
}

void Player::ParseCatchers(std::vector<sf::Vector2f>& a_catcherPositions) {
	m_pMirror->ParseCatchers(a_catcherPositions);
	if (m_pMirror1) m_pMirror1->ParseCatchers(a_catcherPositions);
	if (m_pMirror2) m_pMirror2->ParseCatchers(a_catcherPositions);
	if (m_pMirror3) m_pMirror3->ParseCatchers(a_catcherPositions);
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

		// Place mirror
		if (m_pInputHandler->GetLeftMouseDown() && !m_mousePressed)
		{
			m_mousePressed = true;
			switch (m_activeMirrors) 
			{
				case 0:
					{
						m_pMirror1 = new Mirror(m_resMgr, m_Space);
						m_pMirror1->SetPosition(m_Sprite.sprite->getPosition());
						m_pMirror1->Show();
						++m_activeMirrors;
						break;
					}
				case 1:
					{
						m_pMirror2 = new Mirror(m_resMgr, m_Space);
						m_pMirror2->SetPosition(m_Sprite.sprite->getPosition());
						m_pMirror2->Show();
						++m_activeMirrors;
						break;
					}
				case 2:
					{
						m_pMirror3 = new Mirror(m_resMgr, m_Space);
						m_pMirror3->SetPosition(m_Sprite.sprite->getPosition());
						m_pMirror3->Show();
						++m_activeMirrors;
						break;
					}
			}
		} else {
			m_mousePressed = false;
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

	// Update player's mirror
	m_pMirror->Update(a_Dt);
	if (m_pMirror1) m_pMirror1->Update(a_Dt);
	if (m_pMirror2) m_pMirror2->Update(a_Dt);
	if (m_pMirror3) m_pMirror3->Update(a_Dt);

	//update current mirror
	sf::Vector2f curPos = m_Sprite.sprite->getPosition();
	sf::Vector2u sprSize = m_pMirror->GetSprite()->sprite->getTexture()->getSize();
	curPos.y += 16.f + sprSize.y / 2;
	curPos.x += sprSize.x / 2;
	m_pMirror->SetPosition(curPos);
	m_pMirror->SetRotationAngle(GetAngleFromDir( VectorNormalise(m_pInputHandler->GetMousePos() - curPos) ));
}

void Player::ParseEmitter(Emitter* a_emitter) {
	m_pMirror->ParseEmitter(a_emitter);
	if (m_pMirror1) m_pMirror1->ParseEmitter(a_emitter);
	if (m_pMirror2) m_pMirror2->ParseEmitter(a_emitter);
	if (m_pMirror3) m_pMirror3->ParseEmitter(a_emitter);
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
