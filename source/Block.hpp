#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.hpp"

#include "Defs.hpp"

namespace sf
{
	class Sprite;
}

class Block : public GameObject
{
public:
	enum BlockType {
		BLOCK_SOLID = 0,
		BLOCK_GLASS,
		BLOCK_DOOR,
		BLOCK_START,
		BLOCK_END,
		BLOCK_PLAYER,
		BLOCK_BUTTON
	};
	Block(ResourceManager& a_ResMgr, cpSpace& a_Space, int a_type, sf::Vector2f a_Pos);
	//
	void SetOutput(int a_block);
	const int GetOutput();
	void SetActivated(bool a_state);
	const bool GetActivated();
	const int Type();
	const bool Type(int a_type);
	//
private:
	bool m_activated;
	int m_output;
	int m_blockType;
	sf::Vector2f m_Pos;
	//
	StaticRigidQuad m_BoxBounds;
};

#endif // BLOCK_H