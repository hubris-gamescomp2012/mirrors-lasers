#include "App.hpp"
#include "Renderer.hpp"
#include "WindowManager.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "GUIManager.hpp"
#include "InputHandler.hpp"
#include "Cursor.hpp"

#include "Helpers.hpp"

#include <iostream>

App::App(WindowManager& a_WindowMgr, GUIManager& a_GUIMgr, Renderer& a_Renderer, ResourceManager& a_ResMgr)
:	m_GUIMgr(a_GUIMgr)
,	m_WindowMgr(a_WindowMgr)
,	m_Renderer(a_Renderer)
,	m_ResourceMgr(a_ResMgr)
,	m_pSceneMgr(new SceneManager(a_GUIMgr, m_ResourceMgr, m_Renderer))
	//
,	m_IsQuittingNextUpdate(false)
{
	m_pSceneMgr->SetInputHandler(m_WindowMgr.GetInputHandler());
	//
	sf::Vector2f windowDim = m_WindowMgr.GetWindowDim();
	m_FPSMarker = sfg::Label::Create("FPS: default");
	m_FPSMarker->SetRequisition( sf::Vector2f(100, 20) );
	m_FPSMarker->SetPosition( sf::Vector2f(windowDim.x - 100, 10) );
	//m_FPSMarker->Show(false);
	m_GUIMgr.AddWidget(m_FPSMarker);
	cpSpace* placeholder = NULL;
	m_pCursor = new Cursor(m_ResourceMgr, *placeholder);
	m_pCursor->SetInputHandler(m_WindowMgr.GetInputHandler());
	m_Renderer.AddDrawableSprite(m_pCursor->GetSprite());
}

bool App::Update(float a_Dt)
{
	//process
	bool quit = m_IsQuittingNextUpdate;

	//render everything
	if(m_Renderer.Render(a_Dt))
		quit = true;

	//update fps
	m_FPSMarker->SetText("FPS: " + Num2Str(1/a_Dt));

	//poll for window events
	m_WindowMgr.PollEvents(m_GUIMgr);

	//update the current scene
	m_pSceneMgr->Update(a_Dt);

	//update the cursor
	m_pCursor->Update(a_Dt);

	//check if user has tried to close the application
	if(m_WindowMgr.CheckQuitNextUpdate())
		quit = true;
	if(m_pSceneMgr->CheckQuitNextUpdate())
		quit = true;

	return quit;
}

App::~App()
{
	//
}

bool App::CleanUp()
{
	delete m_pSceneMgr;
	return true;
}
