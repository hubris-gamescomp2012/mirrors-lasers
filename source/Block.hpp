#ifndef BLOCK_H
#define BLOCK_H

#include "ResourceManager.hpp"

namespace sf
{
	class Sprite;
}

class Block
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

	Block(ResourceManager& a_ResMgr, int a_type);
	~Block();
	SpriteID* GetSprite();
	void SetOutput(int a_block);
	const int GetOutput();
	void SetActivated(bool a_state);
	const bool GetActivated();
	const int Type();
	const bool Type(int a_type);
private:
	ResourceManager& m_resMgr;
	SpriteID m_pSprite;
	bool m_activated;
	int m_output;
	int m_blockType;
};

#endif // BLOCK_H