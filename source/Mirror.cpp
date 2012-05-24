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
	m_resMgr.CreateSprite("media/mirror.png", &m_Sprite);
	
	//create the physbody
	cpFloat length = m_Sprite.sprite->getTexture()->getSize().x;
	cpFloat mass = 1;

	//moment of inertia (rotation thing)
	cpFloat moment = cpMomentForSegment(mass, cpv(0,0), cpv(0,0));

	//create physbody
	m_pBody = cpSpaceAddBody(&a_Space, cpBodyNew(mass, moment));
	m_pBody->data = this;
	cpBodySetPos(m_pBody, cpv(500, 500));

	//create collision detection shape
	sf::Vector2u sprSize = m_Sprite.sprite->getTexture()->getSize();
	m_pShape = cpSpaceAddShape( &a_Space, cpSegmentShapeNew(m_pBody, cpv(0,sprSize.y), cpv(sprSize.x,sprSize.y), 1) );
	cpShapeSetFriction(m_pShape, 0);
	m_pShape->data = this;

	cpShapeSetCollisionType(m_pShape, MIRROR);
}

Mirror::~Mirror()
{
	cpShapeFree(m_pLineSegment);
}

void Mirror::Update(float a_Dt)
{
	//
}
