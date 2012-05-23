#include "Block.hpp"

#include "Defs.hpp"

#include <iostream>
#include <SFML\Graphics\Sprite.hpp>

Block::Block(ResourceManager& a_ResMgr, cpSpace& a_Space, int a_type, sf::Vector2f a_Pos)
:	GameObject(a_ResMgr, a_Space)
,	m_activated(false)
,	m_output(-1)
,	m_blockType(a_type)
{
	m_Pos = a_Pos;
	MyType = GameObject::BLOCK;
	// Set sprite based on type
	switch(m_blockType) {
		case BLOCK_SOLID:
			m_resMgr.CreateSprite("media/block_wall_32x32.png", &m_Sprite);
			break;
		case BLOCK_GLASS:
			//
			m_resMgr.CreateSprite("media/block_glass_32x32.png", &m_Sprite);
			break;
		case BLOCK_DOOR:
			//
			m_resMgr.CreateSprite("media/block_wall_32x32.png", &m_Sprite);
			break;
		case BLOCK_PLAYER:
			//
			m_resMgr.CreateSprite("media/block_wall_32x32.png", &m_Sprite);
			break;
		case BLOCK_START:
			//
			m_resMgr.CreateSprite("media/block_wall_32x32.png", &m_Sprite);
			break;
		case BLOCK_END:
			//
			m_resMgr.CreateSprite("media/block_wall_32x32.png", &m_Sprite);
			break;
		default:
			std::cout << "invalid block type!\n";
			break;
	}
	
	//get the space static body
	//m_pBody = a_Space.staticBody;
	
	//create four line segments
	/*m_BoxBounds.Top = cpSegmentShapeNew(m_pBody, cpv(cpFloat(0), cpFloat(0)), cpv(cpFloat(0), cpFloat(0))
	cpShapeSetFriction(m_pShape, 0.5);
	cpSpaceAddShape(&a_Space, m_pShape);*/

	/*
	//define shape verts
	cpVect verts[4];
	verts[0].x = 0;
	verts[0].y = 0;
	verts[1].x = 1;
	verts[1].y = 0;
	verts[2].x = 1;
	verts[2].y = 1;
	verts[3].x = 0;
	verts[3].y = 1;

	//create the shape
	m_pShape = cpPolyShapeNew(m_pBody, 4, verts, cpVect());
	cpShapeSetFriction(m_pShape, 0.5);
	cpSpaceAddShape(&a_Space, m_pShape);
	*/

	/*
	body = cpSpaceAddBody(space, cpBodyNew(4.0f, INFINITY));
	body->p = cpv(100 + j*60, -200 + i*60);
			
	shape = cpSpaceAddShape(space, cpBoxShapeNew(body, 50, 50));
	shape->e = 0.0f; shape->u = 0.7f;
	*/

	//create the physbody
	cpFloat width = 32;
	cpFloat height = 32;
	cpFloat mass = 1;

	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	//cpFloat moment = cpMomentForBox(mass, width, height);

	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	//m_pBody = cpSpaceGetStaticBody(&a_Space);//cpSpaceAddBody(&a_Space, cpBodyNew(mass, moment));//
	//m_pBody->data = this;
	//cpBodySetPos(m_pBody, cpv(500, 500));

	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	//m_pShape = cpSpaceAddShape(&a_Space, cpBoxShapeNew(m_pBody, width, height));
	//cpShapeSetFriction(m_pShape, 0.7);
	//m_pShape->data = this;
	//
	
	float offSet = 32;
	//top
	m_BoxBounds.Top = cpSegmentShapeNew(a_Space.staticBody, cpv(a_Pos.x-offSet, a_Pos.y-offSet), cpv(a_Pos.x, a_Pos.y-offSet), 1);
	m_BoxBounds.Top->collision_type = SURFACE_TOP;
	m_BoxBounds.Top->data = this;
	cpShapeSetFriction(m_BoxBounds.Top, 0.5);
	cpSpaceAddShape(&a_Space, m_BoxBounds.Top);
	//bottom
	m_BoxBounds.Bottom = cpSegmentShapeNew(a_Space.staticBody, cpv(a_Pos.x-offSet, a_Pos.y), cpv(a_Pos.x, a_Pos.y), 1);
	m_BoxBounds.Bottom->collision_type = SURFACE_BOTTOM;
	m_BoxBounds.Bottom->data = this;
	cpShapeSetFriction(m_BoxBounds.Bottom, 0.5);
	cpSpaceAddShape(&a_Space, m_BoxBounds.Bottom);
	//left
	m_BoxBounds.Left = cpSegmentShapeNew(a_Space.staticBody, cpv(a_Pos.x-offSet, a_Pos.y), cpv(a_Pos.x-offSet, a_Pos.y-offSet), 1);
	m_BoxBounds.Left->collision_type = SURFACE_LEFT;
	m_BoxBounds.Left->data = this;
	cpShapeSetFriction(m_BoxBounds.Left, 0.5);
	cpSpaceAddShape(&a_Space, m_BoxBounds.Left);
	//right
	m_BoxBounds.Right = cpSegmentShapeNew(a_Space.staticBody, cpv(a_Pos.x, a_Pos.y-offSet), cpv(a_Pos.x, a_Pos.y), 1);
	m_BoxBounds.Right->collision_type = SURFACE_RIGHT;
	m_BoxBounds.Right->data = this;
	cpShapeSetFriction(m_BoxBounds.Right, 0.5);
	cpSpaceAddShape(&a_Space, m_BoxBounds.Right);

	m_Sprite.sprite->setPosition(m_Pos);
}

void Block::SetOutput(int a_output) {
	m_output = a_output;
}

const int Block::GetOutput() {
	return m_output;
}

void Block::SetActivated(bool a_state) {
	m_activated = a_state;
}

const bool Block::GetActivated() {
	return m_activated;
}

const int Block::Type() {
	return m_blockType;
}

const bool Block::Type(int a_type) {
	if (a_type == m_blockType) return true;
	return false;
}
