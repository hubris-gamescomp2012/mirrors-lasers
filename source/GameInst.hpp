#ifndef GAME_INST_HPP
#define GAME_INST_HPP

#include "Scene.hpp"
#include "SelectListener.hpp"

/*#include <SFGUI/Button.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Notebook.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/Label.hpp>*/

class GameInst : public Scene
{
public:
	GameInst(GUIManager& a_GUIMgr);
	bool Start();
	void Stop();
	virtual void Update(float a_dt);
	virtual void UpdateGUISizes();
	//
	//sfg::Button::Ptr m_pQuitMenuButton;
	//sfg::Notebook::Ptr m_pListView;
	//sfg::Window::Ptr m_pDetailView;
	//
	void Select(void* a_pSelectee, SelectListener::Type a_SelectedType);
	//
private:
	//
	bool m_Running;
	SelectListener* m_pSelectListener;
	//
};

#endif	//GAME_INST_HPP