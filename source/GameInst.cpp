#include "GameInst.hpp"
#include "GUIManager.hpp"
#include "Helpers.hpp"
#include "block.hpp"
#include "Renderer.hpp"
#include "Player.hpp"
#include "Emitter.hpp"

#include "Defs.hpp"
#include "GameInst_callbacks.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#define PHYS_UPDATE_INTERVAL 1.f/120.f

GameInst::GameInst(GUIManager& a_GUIMgr, ResourceManager& a_ResMgr, Renderer& a_Renderer)
:	Scene(a_GUIMgr, a_ResMgr, a_Renderer)
,	m_Running(false)
,	m_Renderer(a_Renderer)
,	m_pQuitMenuButton(sfg::Button::Create("Quit to Main Menu"))
,	laserRotation(2.5f)
,	m_ResMgr(a_ResMgr)
,	m_tLeftPhysUpdate(PHYS_UPDATE_INTERVAL)
	//
{
	//grab the screen dimensions
	sf::Vector2f windowDim = m_GUIMgr.GetWindowDim();

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
}

bool GameInst::Start()
{
	m_Running = true;
	
	// Load the level
	LoadLevel();

	//enable user input to the player
	m_pPlayer->SetInputHandler(m_pInputHandler);

	return true;
}

void GameInst::LoadLevel()
{
	sf::Vector2f windowDim = m_GUIMgr.GetWindowDim();

	//-------------------------------------- chipmunk physics
	// cpVect is a 2D vector and cpv() is a shortcut for initializing them.
	cpVect gravity = cpv(0, 980);
  
	// Create a physworld
	m_pSpace = cpSpaceNew();
	cpSpaceSetGravity(m_pSpace, gravity);

	cpFloat offSet = 0;
	//top
	m_WorldBounds.Top = cpSegmentShapeNew(m_pSpace->staticBody, cpv(offSet,offSet), cpv(cpFloat(windowDim.x)+offSet,offSet), 1);
	cpShapeSetFriction(m_WorldBounds.Top, 0.5);
	cpSpaceAddShape(m_pSpace, m_WorldBounds.Top);
	cpShapeSetCollisionType(m_WorldBounds.Top, SURFACE_BOTTOM);
	//bottom
	m_WorldBounds.Bottom = cpSegmentShapeNew(m_pSpace->staticBody, cpv(offSet,cpFloat(windowDim.y)+offSet), cpv(cpFloat(windowDim.x)+offSet,cpFloat(windowDim.y)+offSet), 1);
	cpShapeSetFriction(m_WorldBounds.Bottom, 0.5);
	cpSpaceAddShape(m_pSpace, m_WorldBounds.Bottom);
	cpShapeSetCollisionType(m_WorldBounds.Bottom, SURFACE_TOP);
	//left
	m_WorldBounds.Left = cpSegmentShapeNew(m_pSpace->staticBody, cpv(offSet,offSet), cpv(offSet,cpFloat(windowDim.y)+offSet), 1);
	cpShapeSetFriction(m_WorldBounds.Left, 0.5);
	cpSpaceAddShape(m_pSpace, m_WorldBounds.Left);
	cpShapeSetCollisionType(m_WorldBounds.Left, SURFACE_RIGHT);
	//right
	m_WorldBounds.Right = cpSegmentShapeNew(m_pSpace->staticBody, cpv(cpFloat(windowDim.x)+offSet,offSet), cpv(cpFloat(windowDim.x)+offSet,cpFloat(windowDim.y)+offSet), 1);
	cpShapeSetFriction(m_WorldBounds.Right, 0.5);
	cpSpaceAddShape(m_pSpace, m_WorldBounds.Right);
	cpShapeSetCollisionType(m_WorldBounds.Right, SURFACE_LEFT);
	
	//player-surface collision callbacks
	cpSpaceAddCollisionHandler(m_pSpace,PLAYER, SURFACE_TOP,cpCollisionBeginFunc(PlayerSurfaceCollision),NULL,NULL,NULL,NULL);
	cpSpaceAddCollisionHandler(m_pSpace,PLAYER, SURFACE_BOTTOM,cpCollisionBeginFunc(PlayerSurfaceCollision),NULL,NULL,NULL,NULL);
	cpSpaceAddCollisionHandler(m_pSpace,PLAYER, SURFACE_LEFT,cpCollisionBeginFunc(PlayerSurfaceCollision),NULL,NULL,NULL,NULL);
	cpSpaceAddCollisionHandler(m_pSpace,PLAYER, SURFACE_RIGHT,cpCollisionBeginFunc(PlayerSurfaceCollision),NULL,NULL,NULL,NULL);

	//load level data from file
	std::fstream file;
	file.open(("media/level1.txt"));
	std::string line;
	int curLine = 0;

	while( std::getline(file,line) )
	{
		//
		for(unsigned int i = 0; i < line.size();i++)
		{
			bool playerMade = false;
			char c = line[i];
			switch(c)
			{
			case('p'):
				{
					//create player
					if (!playerMade) {
						m_pPlayer = new Player(m_ResMgr, *m_pSpace);
						m_pPlayer->SetPosition(float(i)*32, float(curLine)*32);
						m_Renderer.AddDrawableSprite(m_pPlayer->GetSprite());
						playerMade = true;
					}
					break;
				}
			case('#'):
				{
					Block *block = new Block(m_ResMgr, *m_pSpace, Block::BLOCK_SOLID, sf::Vector2f(float(i)*32,float(curLine)*32) );
					m_blocks.push_back(block);
					m_Renderer.AddDrawableSprite(block->GetSprite());
					break;
				}
			case('>'):
				{
					Emitters.push_back(new Emitter(m_ResMgr, *m_pSpace, sf::Vector2f(float(i * 32), float(curLine * 32)) ));
					Emitters.back()->Show();
					break;
				}
			case('<'):
				{
					/*Emitters.push_back(new Emitter(m_ResMgr, *m_pSpace));
					Emitters.back()->SetPosition(i * 32, curLine * 32);
					m_Renderer.AddDrawableSprite(Emitters.back()->GetSprite());*/
					Block *block = new Block(m_ResMgr, *m_pSpace, Block::BLOCK_END, sf::Vector2f(float(i)*32,float(curLine)*32) );
					m_blocks.push_back(block);
					m_Renderer.AddDrawableSprite(block->GetSprite());
					catcherPositions.push_back(block->GetSprite()->sprite->getPosition());
					break;
				}
			}
			//
		}
		curLine++;
	}
	file.close();

	//rebuild static level geometry
	//cpSpaceRehashStatic();
}

void GameInst::UnloadLevel()
{
	// Clear blocks
	for (auto it = m_blocks.begin(); it != m_blocks.end();)
	{
		m_Renderer.RemoveDrawableSprite((*it)->GetSprite());
		it = m_blocks.erase(it);
	}

	//clear laser catchers
	/*for (auto it = Catchers.begin(); it != Catchers.end();)
	{
		it = Catchers.erase(it);
		m_Renderer.RemoveDrawableSprite((*it)->GetSprite());
	}*/

	//clear laser emitters
	for (auto it = Emitters.begin(); it != Emitters.end();)
	{
		m_Renderer.RemoveDrawableSprite((*it)->GetSprite());
		delete *it;
		it = Emitters.erase(it);
	}

	//clear physworld
	cpShapeFree(m_WorldBounds.Top);
	cpShapeFree(m_WorldBounds.Bottom);
	cpShapeFree(m_WorldBounds.Left);
	cpShapeFree(m_WorldBounds.Right);
	cpSpaceFree(m_pSpace);

	//clear player
	m_Renderer.RemoveDrawableSprite(m_pPlayer->GetSprite());
	delete m_pPlayer;
	m_pPlayer = NULL;
}

void GameInst::Stop()
{
	m_Running = false;

	//disable user input to the player
	m_pPlayer->SetInputHandler(NULL);

	UnloadLevel();
	
}

void GameInst::Update(float a_dt)
{
	if(m_Running)
	{
		//update physworld
		/*m_tLeftPhysUpdate -= a_dt;
		if(m_tLeftPhysUpdate < 0)
		{
			m_tLeftPhysUpdate = PHYS_UPDATE_INTERVAL;
		}*/
		cpSpaceStep(m_pSpace, a_dt);

		//update player
		m_pPlayer->Update(a_dt);

		//update emitters (emitters update their own laser chains)
		for (auto it = Emitters.begin(); it != Emitters.end();++it)
		{
			(*it)->Update(a_dt);
			(*it)->ParseCatchers(catcherPositions);
			
			if ((*it)->GetWon()) {
				static bool won = false;
				if (!won) {
					sf::Image image;
					image.loadFromFile("media/wintext.png");
					sfg::Image::Ptr winText = sfg::Image::Create(image);
					winText->SetPosition(sf::Vector2f(512-(float)image.getSize().x/2,386-(float)image.getSize().y/2));

					m_GUIMgr.AddWidget(winText);
					//Widgets.push_back(winText);
					won = true;
				}
			}
		}
		
		//update blocks
		for (auto it = m_blocks.begin(); it != m_blocks.end();++it)
		{
			(*it)->Update(a_dt);
		}		
	}
}

void GameInst::UpdateGUISizes()
{
	//
}

float GameInst::GetLaserRot() {
	return laserRotation;
}

void GameInst::SetLaserRot(float a_rot) {
	laserRotation = a_rot;
}
