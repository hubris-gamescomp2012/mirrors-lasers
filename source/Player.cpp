#include "Player.hpp"

Player::Player(cpSpace& a_Space)
:	m_pShape(NULL)
,	m_pBody(NULL)
{
	cpFloat width = 32;
	cpFloat height = 32;
	cpFloat mass = 1;

	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForBox(mass, width, height);

	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	m_pBody = cpSpaceAddBody(&a_Space, cpBodyNew(mass, moment));
	cpBodySetPos(m_pBody, cpv(500, 500));

	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	m_pShape = cpSpaceAddShape(&a_Space, cpBoxShapeNew(m_pBody, width, height));
	cpShapeSetFriction(m_pShape, 0.7);
}

Player::~Player()
{
	if(m_pBody)
		cpBodyFree(m_pBody);
	if(m_pShape)
		cpShapeFree(m_pShape);
}
