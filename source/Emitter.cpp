#include "Emitter.hpp"
#include "Laser.hpp"
#include "Animator.hpp"

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>

Emitter::Emitter(ResourceManager& a_ResMgr, cpSpace& a_Space, sf::Vector2f a_StartPos)
:	GameObject(a_ResMgr, a_Space)
,	m_Space(a_Space)
,	m_pAnimator(NULL)
{
	MyType = EMITTER;
	//
	m_resMgr.CreateSprite("media/Transmitter_on_32x32.png", &m_Sprite);
	sf::Vector2u sprSize = sf::Vector2u(32, 32);
	m_pAnimator = new Animator(m_Sprite, 32, 32, 3, 8, 10, 24);
	m_Sprite.sprite->setPosition(a_StartPos);

	float offSet = 0;
	//top
	m_BoxBounds.Top = cpSegmentShapeNew(a_Space.staticBody, cpv(a_StartPos.x, a_StartPos.y), cpv(a_StartPos.x + sprSize.x, a_StartPos.y), 1);
	m_BoxBounds.Top->collision_type = SURFACE_TOP;
	m_BoxBounds.Top->data = this;
	cpShapeSetFriction(m_BoxBounds.Top, 0.5);
	cpSpaceAddShape(&a_Space, m_BoxBounds.Top);
	//bottom
	m_BoxBounds.Bottom = cpSegmentShapeNew(a_Space.staticBody, cpv(a_StartPos.x, a_StartPos.y + sprSize.y), cpv(a_StartPos.x + sprSize.x, a_StartPos.y + sprSize.y), 1);
	m_BoxBounds.Bottom->collision_type = SURFACE_BOTTOM;
	m_BoxBounds.Bottom->data = this;
	cpShapeSetFriction(m_BoxBounds.Bottom, 0.5);
	cpSpaceAddShape(&a_Space, m_BoxBounds.Bottom);
	//left
	m_BoxBounds.Left = cpSegmentShapeNew(a_Space.staticBody, cpv(a_StartPos.x, a_StartPos.y + sprSize.y), cpv(a_StartPos.x, a_StartPos.y), 1);
	m_BoxBounds.Left->collision_type = SURFACE_LEFT;
	m_BoxBounds.Left->data = this;
	cpShapeSetFriction(m_BoxBounds.Left, 0.5);
	cpSpaceAddShape(&a_Space, m_BoxBounds.Left);
	//right
	m_BoxBounds.Right = cpSegmentShapeNew(a_Space.staticBody, cpv(a_StartPos.x + sprSize.x, a_StartPos.y), cpv(a_StartPos.x + sprSize.x, a_StartPos.y + sprSize.y), 1);
	m_BoxBounds.Right->collision_type = SURFACE_RIGHT;
	m_BoxBounds.Right->data = this;
	cpShapeSetFriction(m_BoxBounds.Right, 0.5);
	cpSpaceAddShape(&a_Space, m_BoxBounds.Right);
	
	a_StartPos.y += 16;	//move it into the middle of the emitter
	a_StartPos.x += 32;	//move it in front of the emitter
	m_pStartLaser = new Laser(a_ResMgr, a_Space, a_StartPos);
	m_pStartLaser->SetFacingDir(sf::Vector2f(1,0));
	m_pStartLaser->Show();
	
}

sf::Vector2f Emitter::GetHitPoint() {
	return m_pStartLaser->GetHitPoint();
}

void Emitter::Update(float a_Dt)
{
	if(m_pAnimator)
		m_pAnimator->Update(a_Dt);

	if(m_pStartLaser)
		m_pStartLaser->Update(a_Dt);
}

void Emitter::ParseCatchers(std::vector<sf::Vector2f>& a_catcherPositions) {
	m_pStartLaser->SetCatchers(a_catcherPositions);
}

void Emitter::BlockLaser(sf::Vector2f a_blockPos) {
	m_pStartLaser->BlockLaser(a_blockPos);
}

Emitter::~Emitter()
{
	//clear bounding box
	cpShapeFree(m_BoxBounds.Top);
	cpShapeFree(m_BoxBounds.Bottom);
	cpShapeFree(m_BoxBounds.Left);
	cpShapeFree(m_BoxBounds.Right);

	//clear laser
	Laser* pCurLaser = m_pStartLaser;
	while(pCurLaser)
	{
		Laser* laserPtr = pCurLaser;
		m_resMgr.RemoveDrawableSprite(pCurLaser->GetSprite());
		pCurLaser = pCurLaser->GetNextSegment();
		delete laserPtr;
	}

	//clear anim

	if (m_pAnimator) 
		delete m_pAnimator;

	goto MilesPleaseRememberToDeleteStuffThatYouCreateWithTheNewCommandAndPleaseRefrainFromUsingGotosThanksRegardsJohan;
	MilesPleaseRememberToDeleteStuffThatYouCreateWithTheNewCommandAndPleaseRefrainFromUsingGotosThanksRegardsJohan:{}
	//you're so funny
}

bool Emitter::GetWon() {
	return m_pStartLaser->GetWon();
}
