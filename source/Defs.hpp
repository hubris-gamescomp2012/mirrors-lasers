#ifndef DEFS_HPP
#define DEFS_HPP

struct cpShape;

struct StaticRigidQuad
{
	cpShape* Top;
	cpShape* Left;
	cpShape* Bottom;
	cpShape* Right;
};

enum COLLIDABLE
{
	INVALID = 0,
	//
	SURFACE_BOTTOM,
	SURFACE_TOP,
	SURFACE_LEFT,
	SURFACE_RIGHT,
	//
	MIRROR,
	//
	MIRROR_BOTTOM,
	MIRROR_TOP,
	MIRROR_LEFT,
	MIRROR_RIGHT,
	//
	PLAYER,
	LASER,
	//
	MAX
};

#endif	//DEFS_HPP