#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>

namespace sf
{
	class Event;
};

class InputHandler
{
public:
	InputHandler();
	void HandleInputEvent(sf::Event& a_Event);
	//
	int GetKeyDown(int a_KeyCode);	//returns a 1 if down, 0 if nonexistent key or key up
	sf::Vector2f GetMousePos();
private:
	std::vector<int> KeysDown;
	sf::Vector2f m_MousePos;
	//
};

#endif	//INPUT_HANDLER_HPP