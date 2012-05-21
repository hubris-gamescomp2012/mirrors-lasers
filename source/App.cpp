#include "App.hpp"
#include "Renderer.hpp"
#include "WindowManager.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "GUIManager.hpp"

#include <iostream>

App::App(WindowManager& a_WindowMgr, GUIManager& a_GUIMgr, Renderer& a_Renderer)
:	m_GUIMgr(a_GUIMgr)
,	m_WindowMgr(a_WindowMgr)
,	m_Renderer(a_Renderer)
,	m_pResourceMgr(new ResourceManager())
,	m_pSceneMgr(new SceneManager(a_GUIMgr, *m_pResourceMgr, m_Renderer))
	//
,	m_IsQuittingNextUpdate(false)
{
	//
}

bool App::Update(float a_Dt)
{
	//process
	bool quit = m_IsQuittingNextUpdate;

	//render everything
	if(m_Renderer.Render(a_Dt))
		quit = true;

	//poll for window events
	m_WindowMgr.PollEvents(m_GUIMgr);

	//update the current scene
	m_pSceneMgr->Update(a_Dt);

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
	//
	return true;
}
