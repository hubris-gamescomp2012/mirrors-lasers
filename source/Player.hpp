#ifndef	PLAYER_HPP
#define PLAYER_HPP

#include <chipmunk\chipmunk.h>

class Player
{
public:
	Player(cpSpace& a_Space);
	~Player();
	//
private:
	cpBody *m_pBody;
	cpShape *m_pShape;
	//
};

#endif	//PLAYER_HPP