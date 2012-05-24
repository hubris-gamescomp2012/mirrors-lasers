#include "Mirror.hpp"

#include "Defs.hpp"

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>

#include <chipmunk\chipmunk.h>

Mirror::Mirror(ResourceManager& a_ResMgr, cpSpace& a_Space)
:	GameObject(a_ResMgr, a_Space)
{
	//create le sprite
	m_resMgr.CreateSprite("media/mirror2.png", &m_Sprite);
	m_resMgr.AddDrawableSprite(&m_Sprite);
	sf::Vector2u sprSize = m_Sprite.sprite->getTexture()->getSize();
	m_Sprite.sprite->setOrigin(sprSize.x/2,sprSize.y/2);
	
	//moment of inertia (rotation thing)
	cpFloat length = m_Sprite.sprite->getTexture()->getSize().x;
	cpFloat mass = 1;
	cpFloat moment = cpMomentForSegment(mass, cpv(0,0), cpv(0,length));

	//---------------top
	//create physbody
	m_pReflectBody = cpSpaceAddBody(&a_Space, cpBodyNew(mass, moment));
	m_pReflectBody->data = this;
	//create collision line
	m_pReflectLine = cpSpaceAddShape( &a_Space, cpSegmentShapeNew(m_pReflectBody, cpv(0,0), cpv(sprSize.x,0), 1) );
	cpShapeSetFriction(m_pReflectLine, 0);
	m_pReflectLine->data = this;
	m_pReflectLine->sensor = 1;
	
	//only have the reflect line call the callbacks
	cpShapeSetCollisionType(m_pReflectLine, MIRROR);

	//---------------bottom
	//create physbody
	m_pBody = cpSpaceAddBody(&a_Space, cpBodyNew(mass, moment));
	m_pBody->data = this;
	//create collision line
	m_pShape = cpSpaceAddShape( &a_Space, cpSegmentShapeNew(m_pBody, cpv(0,sprSize.y), cpv(sprSize.x,sprSize.y), 1) );
	cpShapeSetFriction(m_pShape, 0);
	m_pShape->data = this;
}

Mirror::~Mirror()
{
	cpBodyFree(m_pReflectBody);
	cpShapeFree(m_pReflectLine);
}

void Mirror::Update(float a_Dt)
{
	//
}

/*
cpFloat cpBodyGetAngle(const cpBody *body)
void cpBodySetAngle(cpBody *body, cpFloat a)
//rotation in radians
*/

void Mirror::SetRotationAngle(float a_Angle)
{
	//rotate physbodies
	cpBodySetAngle(m_pBody, cpFloat(a_Angle));
	cpBodySetAngle(m_pReflectBody, cpFloat(a_Angle));

	//rotate sprite
	m_Sprite.sprite->setRotation( (a_Angle * 180) / 3.14159265f );
}

//2pi r = 360 c
//pi r = 180 c
//1 r = 180/pi c
//pi / 180 r = 1 c
float Mirror::GetRotationAngle()
{
	return float(cpBodyGetAngle(m_pReflectBody));
}
