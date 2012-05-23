#ifndef GAMEINST_CALLBACKS_HPP
#define GAMEINST_CALLBACKS_HPP

#include <chipmunk\chipmunk.h>
#include "Player.hpp"
#include "Defs.hpp"

static cpBool PlayerSurfaceCollision(cpArbiter *arb, struct cpSpace *space, void *data)
{
	//
	Player* pPlayer = (Player*)arb->a_private->data;
	cpShape* pColShape = arb->b_private;
	if(pPlayer && pColShape)
	{
		switch(pColShape->collision_type)
		{
		case(SURFACE_TOP):
			{
				pPlayer->SetOnGround();
				//
				break;
			}
		case(SURFACE_BOTTOM):
			{
				//
				break;
			}
		case(SURFACE_LEFT):
			{
				//
				break;
			}
		case(SURFACE_RIGHT):
			{
				//
				break;
			}
		};
	}
	return 1;
};

static cpBool LaserMirrorCollision(cpArbiter *arb, struct cpSpace *space, void *data)
{
	//
	return 1;
};

static cpBool LaserSurfaceCollision(cpArbiter *arb, struct cpSpace *space, void *data)
{
	//
	return 1;
};

#endif	//GAMEINST_CALLBACKS_HPP