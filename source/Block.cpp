#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "block.hpp"
#include <iostream>

Block::Block(ResourceManager& a_ResMgr, int a_type)
: m_resMgr(a_ResMgr)
, m_activated(false)
, m_output(-1)
, m_blockType(a_type)
{
	// Set sprite based on type
	switch(m_blockType) {
		case BLOCK_SOLID:
			m_resMgr.CreateSprite("media/block.png", &m_pSprite);
			break;
		case BLOCK_GLASS:
			//
			break;
		case BLOCK_DOOR:
			//
			break;
		case BLOCK_PLAYER:
			//
			break;
		case BLOCK_START:
			//
			break;
		case BLOCK_END:
			//
			break;
		default:
			std::cout << "invalid block type!\n";
			break;
	}
	
}

Block::~Block() {
	m_resMgr.DeleteSprite(m_pSprite.ID);
}

SpriteID* Block::GetSprite()
{
	return &m_pSprite;
}

void Block::SetOutput(int a_output) {
	m_output = a_output;
}

const int Block::GetOutput() {
	return m_output;
}

void Block::SetActivated(bool a_state) {
	m_activated = a_state;
}

const bool Block::GetActivated() {
	return m_activated;
}

const int Block::Type() {
	return m_blockType;
}

const bool Block::Type(int a_type) {
	if (a_type == m_blockType) return true;
	return false;
}