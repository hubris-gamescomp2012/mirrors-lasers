#ifndef GAMEINST_CALLBACKS_HPP
#define GAMEINST_CALLBACKS_HPP

#include <chipmunk\chipmunk.h>
#include "Player.hpp"
#include "Defs.hpp"

cpBool PlayerSurfaceCollision(cpArbiter *arb, struct cpSpace *space, void *data);

cpBool LaserMirrorCollision(cpArbiter *arb, struct cpSpace *space, void *data);

cpBool LaserSurfaceCollision(cpArbiter *arb, struct cpSpace *space, void *data);

cpBool PlayerMirrorCollision(cpArbiter *arb, struct cpSpace *space, void *data);

cpBool PlayerGlassCollision(cpArbiter *arb, struct cpSpace *space, void *data);

#endif	//GAMEINST_CALLBACKS_HPP