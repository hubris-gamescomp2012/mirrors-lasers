#ifndef LASER_HPP
#define LASER_HPP

#include "GameObject.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Defs.hpp"

#define LASER_VELOCITY 1000.f
#define MAX_LASER_DIST 2000.f

class Animator;

class Laser : public GameObject
{
public:
	Laser(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos, sf::Vector2f a_FacingDir = sf::Vector2f(1,-1));
	~Laser();
	virtual void Update(float a_Dt);
	//
	void ExtendNewSegment(sf::Vector2f a_NewDir);
	Laser* GetNextSegment();
	Laser* GetPreviousSegment();
	//
	void SetFacingDir(sf::Vector2f a_NewDir);
	//virtual void SetPosition(sf::Vector2f a_NewDir);
	void SetCatchers(std::vector<sf::Vector2f>& a_catcherPositions);
	bool GetWon();
	//
private:
	sf::Vector2f m_StartPos;
	sf::Vector2f m_EndPos;
	float m_CurLength;
	float m_MaxLength;
	//
	sf::Vector2f m_FacingDir;
	//
	Laser* m_pNextChainSegment;
	Laser* m_pPreviousSegment;
	//
	cpSpace& m_Space;
	Animator* m_pAnimator;
	SpriteID m_endSprite;
	SpriteID m_reflectSprite;
	bool m_endDrawn;
	bool m_endDrawnHack; // Yay a hack!
	cpVect m_hitPoint;
	bool m_won;

	//std::vector<sf::Vector2f>* m_catcherPositions;
	//
};

#endif // LASER_HPP