#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics/RenderWindow.hpp>

class Renderer;
class WindowManager;
class ResourceManager;
class SceneManager;
class GUIManager;

class App
{
public:
	App(WindowManager& a_WindowMgr, GUIManager& a_GUIMgr, Renderer& a_Renderer, ResourceManager& a_ResMgr);
	~App();
	//
	bool Update(float a_Dt);
	bool CleanUp();
	//
private:
	Renderer& m_Renderer;
	WindowManager& m_WindowMgr;
	ResourceManager& m_ResourceMgr;
	SceneManager* m_pSceneMgr;
	GUIManager& m_GUIMgr;
	//
	bool m_IsQuittingNextUpdate;
};

#endif	//APP_HPP