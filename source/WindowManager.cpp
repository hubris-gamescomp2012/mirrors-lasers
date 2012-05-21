#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>

#include <iostream>

#include "WindowManager.hpp"
#include "GUIManager.hpp"

//#include "Callbacks.hpp"

using namespace sf;

WindowManager::WindowManager()
:	m_pSFMLRenderWindow(new RenderWindow())
,	m_IsQuittingNextUpdate(false)
{
	m_pSFMLRenderWindow->create(sf::VideoMode(1024,768),"Space Economy Sim");
	sf::Image Icon;
	if (Icon.loadFromFile("media/icon[617x480].bmp") && m_pSFMLRenderWindow)
		m_pSFMLRenderWindow->setIcon(617, 480, Icon.getPixelsPtr());
	m_pSFMLRenderWindow->resetGLStates();
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
			}
		case(Event::KeyPressed):
			{
				Callback::KeyPress(curEvent.key);
				break;
			}*/
		case(Event::Closed):
			{
				m_IsQuittingNextUpdate = true;
				break;
			}
		case(Event::KeyPressed):
			{
				if(curEvent.key.code = sf::Keyboard::Escape)
					delete m_pSFMLRenderWindow;
				break;
			}
		default:
			{
				//a_GUIMgr.HandleEvent(curEvent);
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

sf::Vector2f WindowManager::GetWindowDim()
{
	sf::Vector2f out;
	out.y = (float)m_pSFMLRenderWindow->getSize().y;
	out.x = (float)m_pSFMLRenderWindow->getSize().x;
	return out;
}
