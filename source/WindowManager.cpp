#include "WindowManager.hpp"
#include "GUIManager.hpp"
#include "InputHandler.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

using namespace sf;

WindowManager::WindowManager()
:	m_pSFMLRenderWindow(new RenderWindow())
,	m_IsQuittingNextUpdate(false)
,	m_pInputHandler(NULL)
{
	m_pSFMLRenderWindow->create(sf::VideoMode(1024,768),"Hubris Games, QGC 2012 - Mirrors and Lasers");
	sf::Image Icon;
	if (Icon.loadFromFile("media/robicon.jpg") && m_pSFMLRenderWindow)
		m_pSFMLRenderWindow->setIcon(128, 128, Icon.getPixelsPtr());
	m_pSFMLRenderWindow->resetGLStates();
	//m_pSFMLRenderWindow->setVerticalSyncEnabled(true);
	//
	m_pInputHandler = new InputHandler();
}

bool WindowManager::CheckQuitNextUpdate()
{
	return m_IsQuittingNextUpdate;
}

bool WindowManager::Display(double a_Dt)
{
	//show next frame
	m_pSFMLRenderWindow->display();
	return true;
}

void WindowManager::PollEvents(GUIManager& a_GUIMgr)
{
	//poll for events
	sf::Event curEvent;
	while(m_pSFMLRenderWindow->pollEvent(curEvent))
	{
		switch(curEvent.type)
		{
		/*case(Event::MouseButtonPressed):
			{
				Callback::MouseClick(curEvent.mouseButton);
				break;
			}*/
		case(Event::Closed):
			{
				m_IsQuittingNextUpdate = true;
				break;
			}
		case(Event::MouseEntered):
			{
				m_pSFMLRenderWindow->setMouseCursorVisible(false);
				break;
			}
		case(Event::MouseLeft):
			{
				m_pSFMLRenderWindow->setMouseCursorVisible(true);
				break;
			}
		case(Event::KeyPressed):
			{	
				if(curEvent.key.code == sf::Keyboard::Escape)
				{
					m_IsQuittingNextUpdate = true;
					break;
				}
				//fall through
			}
		default:
			{
				//let our current input_handler deal with it
				if(m_pInputHandler)
					m_pInputHandler->HandleInputEvent(curEvent);

				//let the gui know about it too
				a_GUIMgr.HandleEvent(curEvent);
				break;
			}
		}
	}
}

sf::RenderWindow& WindowManager::GetRenderWindow()
{
	return *m_pSFMLRenderWindow;
}

/*bool WindowManager::GetNextEvent(Event& EventReceived)
{
	return m_pSFMLRenderWindow->GetEvent(EventReceived);
}*/

void WindowManager::CleanUp()
{
	m_pSFMLRenderWindow->close();
	delete m_pSFMLRenderWindow;
}

WindowManager::~WindowManager() {
	CleanUp();
}

sf::Vector2f WindowManager::GetWindowDim()
{
	sf::Vector2f out;
	out.y = (float)m_pSFMLRenderWindow->getSize().y;
	out.x = (float)m_pSFMLRenderWindow->getSize().x;
	return out;
}

void WindowManager::SetInputHandler(InputHandler* a_pInputHandler)
{
	m_pInputHandler = a_pInputHandler;
}

InputHandler* WindowManager::GetInputHandler()
{
	return m_pInputHandler;
}
