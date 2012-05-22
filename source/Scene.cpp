#include "Scene.hpp"

#include "App.hpp"
#include "Renderer.hpp"
#include "GUIManager.hpp"
#include "ResourceManager.hpp"
#include "InputHandler.hpp"

#include <iostream>

Scene::Scene(GUIManager& a_GUIMgr, ResourceManager& a_ResMgr, Renderer& a_Renderer)
:	m_GUIMgr(a_GUIMgr)
,	m_ResMgr(a_ResMgr)
,	m_Renderer(a_Renderer)
,	m_pInputHandler(NULL)
{
	//
}

Scene::~Scene()
{
	//
}

void Scene::ShowScene()
{
	sfg::SharedPtr<sfg::Widget> pCurWidget;
	for(unsigned short i=0;i<Widgets.size();i++)
	{
		Widgets[i]->Show();
	}
}

void Scene::HideScene()
{
	sfg::SharedPtr<sfg::Widget> pCurWidget;
	for(unsigned short i=0;i<Widgets.size();i++)
	{
		Widgets[i]->Show(false);
	}
}

void Scene::SetBackground(sf::Sprite* a_pBGImage)
{
	m_pBackgroundImage = a_pBGImage;
}

sf::Sprite* Scene::GetBackground()
{
	return m_pBackgroundImage;
}

void Scene::SetInputHandler(InputHandler* a_pInputHandler)
{
	m_pInputHandler = a_pInputHandler;
}

InputHandler* Scene::GetInputHandler()
{
	return m_pInputHandler;
}
