#include "MainMenu.hpp"
#include "GUIManager.hpp"

#include <SFGUI\Button.hpp>

MainMenu::MainMenu(GUIManager& a_GUIMgr)
:	Scene(a_GUIMgr)
	//
//,	m_Title(sfg::Label::Create("App"))
//,	m_pStartButton(sfg::Button::Create("Start"))
//,	m_pOptionsButton(sfg::Button::Create("Options"))
//,	m_pQuitButton(sfg::Button::Create("Quit"))
{
	/*
	//setup gui
	sf::Vector2f windowDim = m_GUIMgr.GetWindowDim();
	sf::FloatRect allocRect;
	float invHeightScalar = 10;
	float invWidthScalar = 5;
	
	//changing font size is slooooow :(
	//title
	//m_Title = new sfg::Button();
	//sfg::Context::Get().GetEngine().SetProperty("Label", "FontSize", 100.0f);
	m_Title->SetRequisition( sf::Vector2f(windowDim.x / invWidthScalar, windowDim.y / invHeightScalar) );
	allocRect = m_Title->GetAllocation();
	m_Title->SetPosition( sf::Vector2f(windowDim.x/2 - allocRect.width/2, windowDim.y/5 - allocRect.height/2) );
	m_Title->Show(false);
	m_GUIMgr.AddWidget(m_Title);
	Widgets.push_back(m_Title);

	//start button
	//sfg::Context::Get().GetEngine().SetProperty("Button", "FontSize", 20.0f);
	m_pStartButton->SetRequisition( sf::Vector2f(windowDim.x / invWidthScalar, windowDim.y / invHeightScalar) );
	allocRect = m_pStartButton->GetAllocation();
	m_pStartButton->SetPosition( sf::Vector2f(windowDim.x/4 - allocRect.width/2, 2*windowDim.y/5 - allocRect.height/2) );
	m_pStartButton->Show(false);
	m_GUIMgr.AddWidget(m_pStartButton);
	Widgets.push_back(m_pStartButton);
	
	//options button
	//sfg::Context::Get().GetEngine().SetProperty("Button", "FontSize", 20.0f);
	/*m_pOptionsButton->SetRequisition( sf::Vector2f(windowDim.x / invWidthScalar, windowDim.y / invHeightScalar) );
	allocRect = m_pOptionsButton->GetAllocation();
	m_pOptionsButton->SetPosition( sf::Vector2f(windowDim.x/4 - allocRect.width/2, 3*windowDim.y/5 - allocRect.height/2) );
	m_pOptionsButton->Show(false);
	m_GUIMgr.AddWidget(m_pOptionsButton);
	Widgets.push_back(m_pOptionsButton);
	
	//quit button
	//sfg::Context::Get().GetEngine().SetProperty("Button", "FontSize", 20.0f);
	m_pQuitButton->SetRequisition( sf::Vector2f(windowDim.x / invWidthScalar, windowDim.y / invHeightScalar) );
	allocRect = m_pQuitButton->GetAllocation();
	m_pQuitButton->SetPosition( sf::Vector2f(windowDim.x/4 - allocRect.width/2, 4*windowDim.y/5 - allocRect.height/2) );
	m_pQuitButton->Show(false);
	m_GUIMgr.AddWidget(m_pQuitButton);
	Widgets.push_back(m_pQuitButton);*/
}

void MainMenu::Update(float a_dt)
{
	//
}

void MainMenu::UpdateGUISizes()
{
	//
}
