#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <vector>
#include <map>
#include "ResourceManager.hpp"

class MainMenu;
class OptionsMenu;
class GameInst;
class Scene;

class Renderer;
class GUIManager;

class InputHandler;

namespace sf
{
	class Sprite;
};

namespace sfg
{
	class SFGUI;
};

enum SCENE_TYPE
{
	INVALID_SCENE = 0,
	SCENE_MAINMENU,
	SCENE_OPTIONSMENU,
	SCENE_GAMEINST
};

class SceneManager
{
public:
	SceneManager(GUIManager& a_GUIMgr, ResourceManager& a_ResMgr, Renderer& a_Renderer);
	~SceneManager();
	//
	bool EnableSceneByID(SCENE_TYPE a_SceneID);
	void Update(float a_Dt);
	bool CheckQuitNextUpdate();
	//
	void SetInputHandler(InputHandler* a_pInputHandler);
	InputHandler* GetInputHandler();
	//
private:
	//
	void GotoGameScene();
	void GotoOptionsScene();
	void Quit();
	void GotoMenuScene();
	//
	bool m_IsQuittingNextUpdate;
	//
	std::map<SCENE_TYPE,Scene*> Scenes;
	SCENE_TYPE m_CurScene;
	MainMenu* m_pMainMenu;
	OptionsMenu* m_pOptionsMenu;
	GameInst* m_pGameInst;
	//
	ResourceManager& m_ResMgr;
	GUIManager& m_GUIMgr;
	Renderer& m_Renderer;
	//
	InputHandler* m_pInputHandler;
	//
	std::vector<SpriteID> m_sprites;
	//
};

#endif	//SCENE_MANAGER_HPP