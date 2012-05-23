#include "Laser.hpp"
#include "Helpers.hpp"
#include "Defs.hpp"

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>

Laser::Laser(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos)
:	GameObject(a_ResMgr, a_Space)
,	m_pPreviousSegment(NULL)
,	m_pNextChainSegment(NULL)
,	m_StartPos(a_StartPos)
,	m_EndPos(a_StartPos)
,	m_CurLength(0)
,	m_MaxLength(MAX_LASER_DIST)
,	m_Space(a_Space)
{
	m_resMgr.CreateSprite("media/laser_middle_8x8.png", &m_Sprite);
	m_Sprite.sprite->setPosition(a_StartPos);
	m_Sprite.sprite->setOrigin(0,16);
	m_Sprite.sprite->setRotation(GetAngleFromDir(FacingDir));
	//
	
	//create the physbody
	/*
	cpFloat radius = 32;
	cpFloat mass = 1;
	cpFloat moment = cpMomentForCircle(mass, radius, 0, cpv(0,0));

	m_pBody = cpSpaceAddBody(&a_Space, cpBodyNew(mass, moment));
	m_pBody->data = this;
	cpBodySetPos(m_pBody, cpv(a_StartPos.x, a_StartPos.y));

	m_pShape = cpSpaceAddShape(&a_Space, cpCircleShapeNew(m_pBody, radius, cpv(0,0)));
	m_pShape->data = this;
	m_pShape->sensor = 1;

	cpShapeSetCollisionType(m_pShape, LASER);
	*/
}

Laser::~Laser()
{
	Hide();
}

Laser* Laser::GetNextSegment()
{
	return m_pNextChainSegment;
}

Laser* Laser::GetPreviousSegment()
{
	return m_pPreviousSegment;
}

void Laser::Update(float a_Dt)
{
	//raycast to determine the max length of this laser
	cpVect cpStartPos;
	cpStartPos.x = m_StartPos.x;
	cpStartPos.y = m_StartPos.y;
	cpVect cpEndPos = cpStartPos;
	sf::Vector2f sfEndPos = m_StartPos + FacingDir * MAX_LASER_DIST;
	cpEndPos.x += sfEndPos.x;
	cpEndPos.y += sfEndPos.y;
	cpSegmentQueryInfo info;
	info.n = cpv(0,0);
	info.t = 0;
	info.shape = NULL;

	//grab layer and group info 
	cpLayers layers;

	//cast ray
	//cpShape* collided = cpSpaceSegmentQueryFirst(&m_Space, cpStartPos, cpEndPos, 

	//grab the absolute dist
	//m_MaxLength = float(cpSegmentQueryHitDist(cpStartPos, cpEndPos, info));

	//extend or reduce the laser to the max
	if(m_CurLength < m_MaxLength)
	{
		//update end position
		//fuck you, lasers have velocity (but only when they're growing)
		sf::Vector2f newDist = FacingDir * LASER_VELOCITY * a_Dt;
		m_EndPos += newDist;
		m_CurLength += GetVectorMagnitude(newDist);

		//update sprite
		float baseSize = float(m_Sprite.sprite->getTexture()->getSize().x);
		sf::Vector2f diff = m_EndPos - m_StartPos;
		float newSize = GetVectorMagnitude(diff);
		m_Sprite.sprite->setScale(newSize / baseSize, 1);
	}
	else if(m_CurLength > m_MaxLength)
	{
		//update end position
		m_EndPos = m_StartPos + FacingDir * m_MaxLength;
		sf::Vector2f diff = m_EndPos - m_StartPos;
		m_CurLength = GetVectorMagnitude(diff);

		//udpate sprite
		float baseSize = float(m_Sprite.sprite->getTexture()->getSize().x);
		m_Sprite.sprite->setScale(m_CurLength / baseSize, 1);
	}
}

void Laser::Bounce()
{
	/*
	// Calculate and create new laser path
	sf::Vector2f laserPos = sf::Vector2f((float)startX,(float)startY);
	sf::Vector2f laserDir = sf::Vector2f(1.0f,0.0f);
	unsigned int iter = 0;
	while (laserPos.x >= 0 && laserPos.x <= 1024 && laserPos.y >= 0 && laserPos.y <= 768 && iter < m_laserSprites.size()) {
		// Check to see if the laser has hit anything.
		for (auto it = m_blocks.begin(); it != m_blocks.end();++it) {
			sf::Vector2f pos = (*it)->GetSprite()->sprite->getPosition();
			if (pos.x + 48 > laserPos.x + 16 && pos.x < laserPos.x + 16 && pos.y + 48 > laserPos.y + 16 && pos.y < laserPos.y + 16) {

				// Rotate the laser
				float cs = cos(laserRotation);
				float sn = sin(laserRotation);
				laserDir.x = cs * laserDir.x - sn * laserDir.y;
				laserDir.y = sn * laserDir.x + cs * laserDir.y;

				// Normalise the new direction
				float length = sqrtf((laserDir.x*laserDir.x) + (laserDir.y*laserDir.y));
				laserDir.x = laserDir.x / length;
				laserDir.y = laserDir.y / length;

				laserPos.x += laserDir.x * 4;
				laserPos.y += laserDir.y * 4;

				//std::cout << "X: " << laserDir.x << "Y: " << laserDir.y << "\n";
				break; // don't collide with multiple blocks at once
			}
		}

		laserPos.x += laserDir.x * 4;
		laserPos.y += laserDir.y * 4;

		m_laserSprites[iter].sprite->setPosition(laserPos);

		++iter;
	}
	*/
}
