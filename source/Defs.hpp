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
	BOUNDARY,
	BLOCK,
	PLAYER,
	LASER,
	MIRROR,
	//
	MAX
};

#endif	//DEFS_HPP