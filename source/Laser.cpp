#include "Laser.hpp"
#include "Helpers.hpp"
#include "Animator.hpp"
#include "Player.hpp"
#include "Mirror.hpp"

#include <iostream>

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>

Laser::Laser(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos, sf::Vector2f a_FacingDir)
:	GameObject(a_ResMgr, a_Space)
,	m_pPreviousSegment(NULL)
,	m_pNextChainSegment(NULL)
,	m_StartPos(a_StartPos)
,	m_EndPos(a_StartPos)
,	m_CurLength(0)
,	m_MaxLength(MAX_LASER_DIST)
,	m_Space(a_Space)
,	m_FacingDir(a_FacingDir)
,	m_pAnimator(NULL)
,	m_endDrawn(false)
,	m_endDrawnHack(false)
,	m_won(false)
,   m_laserBlocked(false)
//,	m_catcherPositions(NULL)
{
	MyType = LASER;

	m_resMgr.CreateSprite("media/laser_middle_8x8.png", &m_Sprite);
	m_resMgr.CreateSprite("media/End_laser_32x32.png", &m_endSprite);
	m_resMgr.CreateSprite("media/laser_bounce_8x8.png", &m_reflectSprite);
	m_pAnimator = new Animator(m_endSprite, 32, 32, 3, 8, 10, 24);

	m_Sprite.sprite->setPosition(a_StartPos);
	m_Sprite.sprite->setOrigin(0,4);
	m_Sprite.sprite->setRotation(VectorToAngle(m_FacingDir));
}

void Laser::SetStartPos(sf::Vector2f a_startPos) {
	m_StartPos = a_startPos;
}

sf::Vector2f Laser::GetHitPoint() {
	return sf::Vector2f((float)m_hitPoint.x,(float)m_hitPoint.y);
}

Laser::~Laser()
{
	Hide();
	if (m_endDrawn) m_resMgr.RemoveDrawableSprite(&m_endSprite);
	m_resMgr.DeleteSprite(m_endSprite.ID);
	delete m_pAnimator;
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
	m_Sprite.sprite->setPosition(m_StartPos);

	//raycast to determine the max length of this laser
	cpVect cpStartPos;
	cpStartPos.x = m_StartPos.x;
	cpStartPos.y = m_StartPos.y;
	sf::Vector2f addVector = m_FacingDir * MAX_LASER_DIST;
	sf::Vector2f sfEndPos = m_StartPos + addVector;
	cpVect cpEndPos;
	cpEndPos.x = sfEndPos.x;
	cpEndPos.y = sfEndPos.y;
	cpSegmentQueryInfo info;
	info.n = cpv(0,0);
	info.t = 0;
	info.shape = NULL;

	//cast ray
	cpShape* collided = cpSpaceSegmentQueryFirst(&m_Space, cpStartPos, cpEndPos, ~(cpLayers)COLLIDABLE::GLASSBLOCK, CP_NO_GROUP, &info);

	//grab some helper data
	m_MaxLength = float(min( cpSegmentQueryHitDist(cpStartPos, cpEndPos, info), MAX_LASER_DIST ));
	m_hitPoint = cpSegmentQueryHitPoint(cpStartPos, cpEndPos, info);

	//extend or reduce the laser to the max length
	if(m_CurLength < m_MaxLength)
	{
		//update end position
		//fuck you, lasers have velocity (but only when they're growing)
		sf::Vector2f newDist = m_FacingDir * LASER_VELOCITY * a_Dt;
		m_EndPos += newDist;
		m_CurLength += VectorMagnitude(newDist);

		//update sprite
		float baseSize = float(m_Sprite.sprite->getTexture()->getSize().x);
		sf::Vector2f diff = m_EndPos - m_StartPos;
		float newSize = VectorMagnitude(diff);
		m_Sprite.sprite->setScale(newSize / baseSize, 1);
		//m_resMgr.RemoveDrawableSprite(&m_endSprite);
	}
	else
	{
		//update end position
		m_EndPos = m_StartPos + m_FacingDir * m_MaxLength;
		sf::Vector2f diff = m_EndPos - m_StartPos;
		m_endSprite.sprite->setPosition(m_EndPos);
		//sf::Vector2f diff = m_blockPos - m_StartPos;
		m_CurLength = VectorMagnitude(diff);

		//update sprite
		float baseSize = float(m_Sprite.sprite->getTexture()->getSize().x);
		m_Sprite.sprite->setScale(m_CurLength / baseSize, 1);
		//m_resMgr.AddDrawableSprite(&m_endSprite);

		m_endDrawnHack = true;
	}
	
	/*if(m_pNextChainSegment)
	{
		m_pNextChainSegment->Update(a_Dt);
	}*/
}

void Laser::BlockLaser(sf::Vector2f a_blockPos) {
	m_blockPos = a_blockPos;
	m_laserBlocked = true;
}

/*void Laser::ExtendNewSegment(sf::Vector2f a_NewDir)
{
	m_pNextChainSegment = new Laser(m_resMgr, m_Space, m_EndPos, a_NewDir);
	m_pNextChainSegment->m_pPreviousSegment = this;
	m_resMgr.AddDrawableSprite(m_pNextChainSegment->GetSprite());
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
}*/

void Laser::SetFacingDir(sf::Vector2f a_NewDir)
{
	m_FacingDir = a_NewDir;
	/*
	m_resMgr.CreateSprite("media/laser_middle_8x8.png", &m_Sprite);
	m_resMgr.CreateSprite("media/End_laser_32x32.png", &m_endSprite);
	m_resMgr.CreateSprite("media/laser_bounce_8x8.png", &m_reflectSprite);
	m_pAnimator = new Animator(m_endSprite, 32, 32, 3, 8, 10, 24);

	m_Sprite.sprite->setPosition(a_StartPos);
	m_Sprite.sprite->setOrigin(0,4);
	m_Sprite.sprite->setRotation(VectorToAngle(m_FacingDir));
	*/
	m_Sprite.sprite->setRotation(VectorToAngle(m_FacingDir));
	m_endSprite.sprite->setRotation(VectorToAngle(m_FacingDir));

}

void Laser::SetCatchers(std::vector<sf::Vector2f>& a_catcherPositions)
{
	// Check win condition
	if (m_CurLength > m_MaxLength)
	{
		for (auto it = a_catcherPositions.begin(); it != a_catcherPositions.end(); ++it)
		{
			if (it->x - 16 < (float)m_hitPoint.x &&
				it->x + 32 > (float)m_hitPoint.x &&
				it->y - 16 < (float)m_hitPoint.y &&
				it->y + 32 > (float)m_hitPoint.y)
			{
					m_won = true;
					break;
			}
		}
	}
}

bool Laser::GetWon()
{
	return m_won;
}
