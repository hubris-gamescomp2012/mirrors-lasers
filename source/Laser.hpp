#ifndef LASER_H
#define LASER_H

#include <vector>

class Laser {
public:
	Laser(ResourceManager& a_ResMgr);
	void Blocks(std::vector<Block*> a_blocks);
private:
	std::vector<Block*> m_blocks;
	sf::Sprite* m_pSprite;
};

#endif // LASER_H