#include "GameInst_callbacks.hpp"
#include "Laser.hpp"
#include "Mirror.hpp"

cpBool PlayerSurfaceCollision(cpArbiter *arb, struct cpSpace *space, void *data)
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

cpBool LaserMirrorCollision(cpArbiter *arb, struct cpSpace *space, void *data)
{
	Laser* pLaser = (Laser*)arb->a_private->data;
	Mirror* pMirror = (Mirror*)arb->b_private->data;
	return 1;
};

cpBool LaserSurfaceCollision(cpArbiter *arb, struct cpSpace *space, void *data)
{
	//
	return 1;
};

cpBool PlayerMirrorCollision(cpArbiter *arb, struct cpSpace *space, void *data)
{
	//
	return 0;
};

cpBool PlayerGlassCollision(cpArbiter *arb, struct cpSpace *space, void *data)
{
	//
	return 0;
};
