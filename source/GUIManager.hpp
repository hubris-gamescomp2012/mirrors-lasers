#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFGUI/SFGUI.hpp>

namespace sf
{
	class RenderTarget;
};
namespace sfg
{
	class SFGUI;
	class Desktop;
};
class WindowManager;

class GUIManager
{
public:
	GUIManager(WindowManager& a_WindowMgr);
	void RenderGui(sf::RenderWindow& a_RenderWindow);
	void GUIManager::Update(float a_Dt);
	void HandleEvent(sf::Event a_Event);
	sf::Vector2f GetWindowDim();
	//
	//void CreateTestWindow();
	void AddWidget(sfg::SharedPtr<sfg::Widget> a_Widget);
	sfg::Desktop& GetDesktop();
	//
private:
	WindowManager& m_WindowMgr;
	sfg::SFGUI m_sfgui;
	sfg::Desktop m_Desktop;
	//
};

#endif	//GUI_MANAGER_HPP