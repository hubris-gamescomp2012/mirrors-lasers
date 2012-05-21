#ifndef OPTIONS_MENU_HPP
#define OPTIONS_MENU_HPP

#include "Scene.hpp"

class OptionsMenu : public Scene
{
public:
	OptionsMenu(GUIManager& a_GUIMgr, ResourceManager& a_ResMgr, Renderer& a_Renderer);
	virtual void Update(float a_dt);
	virtual void UpdateGUISizes();
	//
private:
	//
};

#endif	//OPTIONS_MENU_HPP