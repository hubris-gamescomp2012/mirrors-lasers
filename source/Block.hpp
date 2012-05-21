#ifndef BLOCK_H
#define BLOCK_H

namespace sf
{
	class Sprite;
}

class Block
{
public:
	Block(ResourceManager& a_ResMgr);
	sf::Sprite* GetSprite();
	//
private:
	sf::Sprite* m_pSprite;
	//
};

#endif // BLOCK_H