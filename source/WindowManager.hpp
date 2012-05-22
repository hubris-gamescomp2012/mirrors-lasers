#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf
{
	class RenderWindow;
	class RenderTarget;
}

class GUIManager;
class InputHandler;

class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	/*static WindowMgr& GetReference()
	{
		static WindowMgr instance;
		return instance;
	}*/
	//bool GetNextEvent(sf::Event& EventReceived);
	sf::Vector2f GetWindowDim();
	sf::RenderWindow& GetRenderWindow();
	//
	void PollEvents(GUIManager& a_GUIMgr);
	bool Display(double a_Dt);
	//
	bool CheckQuitNextUpdate();
	//
	void SetInputHandler(InputHandler* a_pInputHandler);
	InputHandler* GetInputHandler();
	//
	void CleanUp();
private:
	sf::RenderWindow* m_pSFMLRenderWindow;
	bool m_IsQuittingNextUpdate;
	//
	InputHandler* m_pInputHandler;
};

#endif