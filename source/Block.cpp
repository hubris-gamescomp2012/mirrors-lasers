#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "block.hpp"

Block::Block(ResourceManager& a_ResMgr)
: m_pSprite(NULL)
{
	m_pSprite = new sf::Sprite();
	a_ResMgr.CreateSprite("media/block.png", &m_pSprite);
}

sf::Sprite* Block::GetSprite()
{
	return m_pSprite;
}
