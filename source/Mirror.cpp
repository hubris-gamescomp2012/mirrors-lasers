#include "Mirror.hpp"

#include "Defs.hpp"

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>
#include <iostream>
#include <chipmunk\chipmunk.h>

#include "Laser.hpp"
#include "Emitter.hpp"

Mirror::Mirror(ResourceManager& a_ResMgr, cpSpace& a_Space)
:	GameObject(a_ResMgr, a_Space)
,	m_pLaser(NULL)
,	m_pSpace(a_Space)
{
	MyType = GameObject::Type::MIRROR;
	//create le sprite
	m_resMgr.CreateSprite("media/mirror2.png", &m_Sprite);
	m_resMgr.AddDrawableSprite(&m_Sprite);
	sf::Vector2u sprSize = m_Sprite.sprite->getTexture()->getSize();
	m_Sprite.sprite->setOrigin((float)sprSize.x/2,(float)sprSize.y/2);
	
	//moment of inertia (rotation thing)
	cpFloat length = m_Sprite.sprite->getTexture()->getSize().x;
	cpFloat mass = 1;
	cpFloat moment = cpMomentForSegment(mass, cpv(0,0), cpv(length,0));

	//---------------top
	//create physbody
	/*
	m_pReflectBody = cpSpaceAddBody(&a_Space, cpBodyNew(mass, moment));
	m_pReflectBody->data = this;
	//create collision line
	m_pReflectLine = cpSpaceAddShape( &a_Space, cpSegmentShapeNew(m_pReflectBody, cpv(0,sprSize.y), cpv(sprSize.x,sprSize.y), 1) );
	cpShapeSetFriction(m_pReflectLine, 0);
	m_pReflectLine->data = this;
	m_pReflectLine->sensor = 1;
	m_pReflectLine->collision_type = COLLIDABLE::MIRROR_REFLECT;
	
	//only have the reflect line call the callbacks
	cpShapeSetCollisionType(m_pReflectLine, MIRROR);
	cpShapeSetLayers(m_pReflectLine, (cpLayers)MIRROR);*/
	
	//---------------bottom
	//create physbody
	m_pBody = cpSpaceAddBody(&a_Space, cpBodyNew(mass, moment));
	m_pBody->data = this;
	//create collision line
	m_pShape = cpSpaceAddShape( &a_Space, cpSegmentShapeNew(m_pBody, cpv(0,0), cpv(sprSize.x,0), 1) );
	cpShapeSetFriction(m_pShape, 0);
	m_pShape->data = this;
	m_pShape->collision_type = COLLIDABLE::MIRROR;

	cpShapeSetLayers(m_pShape, (cpLayers)MIRROR);
}

Mirror::~Mirror()
{
	if (m_pLaser) {
		m_pLaser->Hide();
		delete m_pLaser;
		m_pLaser = NULL;
	}
	if(m_pReflectBody)
		cpBodyFree(m_pReflectBody);
	if(m_pReflectLine)
		cpShapeFree(m_pReflectLine);
}

void Mirror::Update(float a_Dt)
{
	if (m_pLaser) {
		/*sf::Vector2f direction = sf::Vector2f(0,1);
		float rotation = m_Sprite.sprite->getRotation() * 3.14159265f/180.0f;
		direction.x = cos(rotation) * direction.x - sin(rotation) * direction.y; 
		direction.y = sin(rotation) * direction.x + cos(rotation) * direction.y;
		float length = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= length;
		direction.y /= length;
		m_pLaser->SetFacingDir(direction);
		m_pLaser->Update(a_Dt);*/
	}
}

void Mirror::BlockLaser(sf::Vector2f a_blockPos) {
	if (m_pLaser) m_pLaser->BlockLaser(a_blockPos);
}

void Mirror::ParseEmitter(Emitter* a_emitter) 
{
	/*
	sf::Vector2f hitPoint = a_emitter->GetHitPoint();
	sf::Vector2f spritePos = m_Sprite.sprite->getPosition();

	//std::cout << "SPRITE X:" << spritePos.x << " Y:" << spritePos.y << std::endl;
	//std::cout << "HITPOS X:" << hitPoint.x << " Y:" << hitPoint.y << std::endl;

	if (hitPoint.x + 32 > spritePos.x && hitPoint.x - 16 < spritePos.x && hitPoint.y + 32 > spritePos.y && hitPoint.y - 16 < spritePos.y) {
		if (!m_pLaser) {
			sf::Vector2f direction = sf::Vector2f(0,1);
			float rotation = m_Sprite.sprite->getRotation() * 3.14159265f/180.0f;
			direction.x = cos(rotation) * direction.x - sin(rotation) * direction.y; 
			direction.y = sin(rotation) * direction.x + cos(rotation) * direction.y;
			float length = sqrt(direction.x * direction.x + direction.y * direction.y);
			direction.x /= length;
			direction.y /= length;

			BlockLaser(sf::Vector2f(spritePos.x,spritePos.y));

			m_pLaser = new Laser(m_resMgr, m_pSpace, a_emitter->GetHitPoint(), direction);
			m_pLaser->Show();
		} else {
			m_pLaser->SetStartPos(hitPoint);
		}
	} else {
		if (m_pLaser) {
			m_pLaser->Hide();
			delete m_pLaser;
			m_pLaser = NULL;
		}
	}*/
}

/*
cpFloat cpBodyGetAngle(const cpBody *body)
void cpBodySetAngle(cpBody *body, cpFloat a)
//rotation in radians
*/

void Mirror::SetRotationAngle(float a_Angle)
{
	//
	a_Angle += 3.14159265f / 2;

	//rotate physbodies

	
	cpBodySetAngle(m_pBody, cpFloat(a_Angle));
	//cpBodySetAngle(m_pReflectBody, cpFloat(a_Angle));

	//rotate sprite
	m_Sprite.sprite->setRotation( (a_Angle * 180) / 3.14159265f );
}

//2pi r = 360 c
//pi r = 180 c
//1 r = 180/pi c
//pi / 180 r = 1 c
float Mirror::GetRotationAngle()
{
	return float(cpBodyGetAngle(m_pBody));
}

bool Mirror::GetWon() {
	if (m_pLaser) return m_pLaser->GetWon();
	return false;
}

void Mirror::ParseCatchers(std::vector<sf::Vector2f>& a_catcherPositions) {
	if (m_pLaser) m_pLaser->SetCatchers(a_catcherPositions);
}

void Mirror::SetPosition(sf::Vector2f a_NewPos)
{
	//GameObject::SetPosition(a_NewPos);
	//
	if(m_pBody && m_Sprite.sprite)
	{
		sf::Vector2u sprSize = m_Sprite.sprite->getTexture()->getSize();
		a_NewPos.x += sprSize.x/2;
		a_NewPos.y += 16.f;
		m_Sprite.sprite->setPosition(a_NewPos.x, a_NewPos.y);
		//a_NewPos.y -= 16.f;
		m_pBody->p.x = a_NewPos.x;
		m_pBody->p.y = a_NewPos.y;
		//m_pReflectBody->p.x = a_NewPos.x;
		//m_pReflectBody->p.y = a_NewPos.y;
	}
	else if(m_Sprite.sprite)
	{
		m_Sprite.sprite->setPosition(a_NewPos.x, a_NewPos.y);
	}
}
