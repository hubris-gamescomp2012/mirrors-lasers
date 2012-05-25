#include "InputHandler.hpp"
#include <SFML\Window\Event.hpp>

InputHandler::InputHandler()
: m_LeftMouse(false)
{
	for(unsigned short i=0;i<sf::Keyboard::KeyCount;i++)
	{
		KeysDown.push_back(0);
	}
}

void InputHandler::HandleInputEvent(sf::Event& a_Event)
{
	switch(a_Event.type)
	{
	/*case(Event::MouseButtonPressed):
		{
			Callback::MouseClick(curEvent.mouseButton);
			break;
		}*/
	case(sf::Event::KeyPressed):
		{
			KeysDown[a_Event.key.code] = 1;
			break;
		}
	case(sf::Event::KeyReleased):
		{
			KeysDown[a_Event.key.code] = 0;
			break;
		}
	case(sf::Event::MouseMoved):
		{
			m_MousePos.x = (float)a_Event.mouseMove.x;
			m_MousePos.y = (float)a_Event.mouseMove.y;
			break;
		}
	case(sf::Event::MouseButtonPressed):
		{
			if (a_Event.mouseButton.button == sf::Mouse::Left) m_LeftMouse = true;
			break;
		}
	case(sf::Event::MouseButtonReleased):
		{
			if (a_Event.mouseButton.button == sf::Mouse::Left) m_LeftMouse = false;
			break;
		}
	}
}

int InputHandler::GetKeyDown(int a_KeyCode)
{
	if(unsigned(a_KeyCode) < KeysDown.size())
	{
		return KeysDown[a_KeyCode];
	}
	return 0;
}

bool InputHandler::GetLeftMouseDown() {
	return m_LeftMouse;
}

sf::Vector2f InputHandler::GetMousePos()
{
	return m_MousePos;
}
