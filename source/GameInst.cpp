#include "GameInst.hpp"
#include "GUIManager.hpp"
#include "Helpers.hpp"
#include "block.hpp"
#include "Renderer.hpp"
#include "Player.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

GameInst::GameInst(GUIManager& a_GUIMgr, ResourceManager& a_ResMgr, Renderer& a_Renderer)
:	Scene(a_GUIMgr, a_ResMgr, a_Renderer)
,	m_Running(false)
,	m_Renderer(a_Renderer)
,	m_pQuitMenuButton(sfg::Button::Create("Quit to Main Menu"))
	//
{
	//grab the screen dimensions
	sf::Vector2f windowDim = m_GUIMgr.GetWindowDim();

	//to handle button presses and the like
	m_pSelectListener = new SelectListener(*this);
	/** Create Adjustment.
		* @param value Current value.
		* @param lower Minimum value.
		* @param upper Maximum value.
		* @param minor_step Minor change value (such as clicking on arrow button).
		* @param major_step Major change value (such as clicking on the scroll area).
		* @param page_size Page size (how many entries are visible / slider size).
		* @return Adjustment.
		*/

	//add a systemlist scrollbar
	/*sfg::Scrollbar::Ptr systemScrollBar = sfg::Scrollbar::Create(sfg::Scale::VERTICAL);
	m_pSystemList->Attach(systemScrollBar, sf::Rect<unsigned int>(1,1,1,1), 0, 0);
	sfg::Adjustment::Ptr adjustment = systemScrollBar->GetAdjustment();
	systemScrollBar->SetRequisition( sf::Vector2f( 0.f, windowDim.y/2 ) );

	// Tune the adjustment parameters.
	adjustment->SetLower( 20.f );
	adjustment->SetUpper( 100.f );

	// How much it should change when clicked on the stepper.
	adjustment->SetMinorStep( 1.f );

	// How much it should change when clicked on the trough.
	adjustment->SetMajorStep( 5.f );*/

	//setup gui
	sf::FloatRect allocRect;
	//double invHeightScalar = 10;
	//double invWidthScalar = 5;
	
	//quit to menu button
	//sfg::Context::Get().GetEngine().SetProperty("Button", "FontSize", 20.0f);
	m_pQuitMenuButton->SetRequisition( sf::Vector2f(windowDim.x / 20, windowDim.y / 20) );
	allocRect = m_pQuitMenuButton->GetAllocation();
	m_pQuitMenuButton->SetPosition( sf::Vector2f(5, 5) );
	m_pQuitMenuButton->Show(false);
	m_GUIMgr.AddWidget(m_pQuitMenuButton);
	Widgets.push_back(m_pQuitMenuButton);

	//-------------------------------------- chipmunk physics
	// cpVect is a 2D vector and cpv() is a shortcut for initializing them.
	cpVect gravity = cpv(0, -100);
  
	// Create an empty space.
	m_pSpace = cpSpaceNew();
	cpSpaceSetGravity(m_pSpace, gravity);
  
	// Add a static line segment shape for the ground.
	// We'll make it slightly tilted so the ball will roll off.
	// We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.

	//top
	m_WorldBounds.Bottom = cpSegmentShapeNew(m_pSpace->staticBody, cpv(0, windowDim.y), cpv(windowDim.x, windowDim.y), 0);
	cpShapeSetFriction(m_WorldBounds.Bottom, 1);
	cpSpaceAddShape(m_pSpace, m_WorldBounds.Bottom);
	//bottom
	m_WorldBounds.Bottom = cpSegmentShapeNew(m_pSpace->staticBody, cpv(0, 0), cpv(windowDim.x, 0), 0);
	cpShapeSetFriction(m_WorldBounds.Bottom, 1);
	cpSpaceAddShape(m_pSpace, m_WorldBounds.Bottom);
	//left
	m_WorldBounds.Bottom = cpSegmentShapeNew(m_pSpace->staticBody, cpv(0, 0), cpv(0, windowDim.y), 0);
	cpShapeSetFriction(m_WorldBounds.Bottom, 1);
	cpSpaceAddShape(m_pSpace, m_WorldBounds.Bottom);
	//right
	m_WorldBounds.Bottom = cpSegmentShapeNew(m_pSpace->staticBody, cpv(windowDim.x, 0), cpv(windowDim.x, windowDim.y), 0);
	cpShapeSetFriction(m_WorldBounds.Bottom, 1);
	cpSpaceAddShape(m_pSpace, m_WorldBounds.Bottom);

	m_pPlayer = new Player(*m_pSpace);

	/*
	// Now let's make a ball that falls onto the line and rolls off.
	// First we need to make a cpBody to hold the physical properties of the object.
	// These include the mass, position, velocity, angle, etc. of the object.
	// Then we attach collision shapes to the cpBody to give it a size and shape.

	cpFloat radius = 5;
	cpFloat mass = 1;

	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);

	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	cpBody *ballBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
	cpBodySetPos(ballBody, cpv(0, 15));

	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	cpShape *ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
	cpShapeSetFriction(ballShape, 0.7);
  
	// Now that it's all set up, we simulate all the objects in the space by
	// stepping forward through time in small increments called steps.
	// It is *highly* recommended to use a fixed size time step.
	cpFloat timeStep = 1.0/60.0;
	for(cpFloat time = 0; time < 2; time += timeStep)
	{
		cpVect pos = cpBodyGetPos(ballBody);
		cpVect vel = cpBodyGetVel(ballBody);
		printf(
			"Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
			time, pos.x, pos.y, vel.x, vel.y
		);

		cpSpaceStep(space, timeStep);
	}

	// Clean up our objects and exit!
	cpShapeFree(ballShape);
	cpBodyFree(ballBody);
	cpShapeFree(ground);
	cpSpaceFree(space);
	*/
}

bool GameInst::Start()
{
	m_Running = true;
	LoadLevel();
	return true;
}

void GameInst::LoadLevel()
{
	/*Block *block = new Block(m_ResMgr);
	m_blocks.push_back(block);
	m_Renderer.AddDrawableSprite(block->Sprite());*/
	std::fstream file;
	file.open(("media/level.txt"));
	std::string line;
	int curLine = 0;
	while( std::getline(file,line) )
	{
		//
		for(unsigned int i = 0; i < line.size();i++)
		{
			char c = line[i];
			switch(c)
			{
			case('#'):
				{
					Block *block = new Block(m_ResMgr);
					m_blocks.push_back(block);
					block->GetSprite()->setPosition(float(i)*32,float(curLine)*32);
					m_Renderer.AddDrawableSprite(block->GetSprite());
					break;
				}
			}
			//
		}
		curLine++;
	}
}

void GameInst::UnloadLevel() {
	for (auto it = m_blocks.begin(); it != m_blocks.end();) {
		it = m_blocks.erase(it);
	}
}

void GameInst::Stop()
{
	m_Running = false;
	UnloadLevel();
}

void GameInst::Update(float a_dt)
{
	if(m_Running)
	{
		for (auto it = m_blocks.begin(); it != m_blocks.end();++it)
		{
			//m_Renderer->((*it)->Sprite());
		}
		//
	}
}

void GameInst::UpdateGUISizes()
{
	//
}

void GameInst::Select(void* a_pSelectee, SelectListener::Type a_SelectedType)
{
	//
}
