#include "Scene.hpp"
#include "App.hpp"
#include "Renderer.hpp"
#include "GUIManager.hpp"

//#include <SFGUI/SFGUI.hpp>

#include <iostream>

Scene::Scene(GUIManager& a_GUIMgr)
:	m_GUIMgr(a_GUIMgr)
{
	//
}

Scene::~Scene()
{
	//
}

void Scene::ShowScene()
{
	/*sfg::SharedPtr<sfg::Widget> pCurWidget;
	for(unsigned short i=0;i<Widgets.size();i++)
	{
		Widgets[i]->Show();
	}*/
}

void Scene::HideScene()
{
	/*sfg::SharedPtr<sfg::Widget> pCurWidget;
	for(unsigned short i=0;i<Widgets.size();i++)
	{
		Widgets[i]->Show(false);
	}*/
}

void Scene::SetBackground(sf::Sprite* a_pBGImage)
{
	m_pBackgroundImage = a_pBGImage;
}

sf::Sprite* Scene::GetBackground()
{
	return m_pBackgroundImage;
}
