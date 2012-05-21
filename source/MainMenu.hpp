#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "Scene.hpp"
#include <SFGUI/Label.hpp>
#include <SFGUI/Button.hpp>

class MainMenu : public Scene
{
public:
	MainMenu(GUIManager& a_GUIMgr);
	virtual void Update(float a_dt);
	virtual void UpdateGUISizes();
	//
	sfg::Label::Ptr m_Title;
	sfg::Button::Ptr m_pStartButton;
	sfg::Button::Ptr m_pOptionsButton;
	sfg::Button::Ptr m_pQuitButton;
	//
private:
	//
};

#endif	//MAIN_MENU_HPP