#include "SceneManager.hpp"

#include "Renderer.hpp"
#include "ResourceManager.hpp"
#include "GUIManager.hpp"

#include "InputHandler.hpp"

#include "MainMenu.hpp"
#include "OptionsMenu.hpp"
#include "GameInst.hpp"

#include <SFML/Graphics.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/SFGUI.hpp>

SceneManager::SceneManager(GUIManager& a_GUIMgr, ResourceManager& a_ResMgr, Renderer& a_Renderer)
:	m_ResMgr(a_ResMgr)
,	m_GUIMgr(a_GUIMgr)
,	m_Renderer(a_Renderer)
	//
,	m_CurScene(INVALID_SCENE)
,	m_pMainMenu(NULL)
,	m_pOptionsMenu(NULL)
,	m_pGameInst(NULL)
,	m_pInputHandler(NULL)
	//
,	m_IsQuittingNextUpdate(false)
{
	//--------------- main menu ---------------//
	m_pMainMenu = new MainMenu(m_GUIMgr, m_ResMgr, m_Renderer);

	SpriteID spriteID;
	a_ResMgr.CreateSprite("media/menubackground[1920x1080].jpg", &spriteID);
	m_sprites.push_back(spriteID);

	sf::Sprite* pBG = spriteID.sprite;
	m_pMainMenu->SetBackground(pBG);
	m_pMainMenu->m_pStartButton->OnLeftClick.Connect(&SceneManager::GotoGameScene, this);
	m_pMainMenu->m_pOptionsButton->OnLeftClick.Connect(&SceneManager::GotoOptionsScene, this);
	m_pMainMenu->m_pQuitButton->OnLeftClick.Connect(&SceneManager::Quit, this);
	Scenes[SCENE_MAINMENU] = m_pMainMenu;
	
	//scale bg to fit the screen
	sf::Vector2f screenDim = m_GUIMgr.GetWindowDim();
	sf::FloatRect bgSize;
	float scalar;
	if(pBG)
	{
		bgSize = pBG->getLocalBounds();
		scalar = screenDim.x/bgSize.width;
		if(scalar < screenDim.y/bgSize.height)
			scalar = screenDim.y/bgSize.height;
		pBG->setScale(scalar, scalar);
	}

	//--------------- options menu ---------------//
	m_pOptionsMenu = new OptionsMenu(m_GUIMgr, m_ResMgr, m_Renderer);
	m_pOptionsMenu->SetBackground(pBG);
	Scenes[SCENE_OPTIONSMENU] = m_pOptionsMenu;

	//--------------- application screen ---------------//
	m_pGameInst = new GameInst(m_GUIMgr, m_ResMgr, m_Renderer);

	SpriteID spriteID2;
	a_ResMgr.CreateSprite("media/starry[1280x853].bmp", &spriteID2);
	m_sprites.push_back(spriteID2);

	pBG = spriteID2.sprite;
	m_pGameInst->SetBackground(spriteID2.sprite);
	m_pGameInst->m_pQuitMenuButton->OnLeftClick.Connect(&SceneManager::GotoMenuScene, this);

	Scenes[SCENE_GAMEINST] = m_pGameInst;

	//scale bg to fit the screen
	if(pBG)
	{
		bgSize = pBG->getLocalBounds();
		scalar = screenDim.x/bgSize.width;
		if(scalar < screenDim.y/bgSize.height)
			scalar = screenDim.y/bgSize.height;
		pBG->setScale(scalar, scalar);
	}

	//set the main menu as the first scene
	EnableSceneByID(SCENE_MAINMENU);
}

SceneManager::~SceneManager()
{
	// Clear background images
	for (auto it = m_sprites.begin(); it != m_sprites.end();) {
		m_ResMgr.DeleteSprite((*it).ID);
		it = m_sprites.erase(it);
	}

	// Delete scenes
	delete m_pGameInst;
	delete m_pMainMenu;
	delete m_pOptionsMenu;
}

bool SceneManager::EnableSceneByID(SCENE_TYPE a_SceneID)
{
	if(m_CurScene)
	{
		Scenes[m_CurScene]->HideScene();
	}
	if(a_SceneID)
	{
		m_CurScene = a_SceneID;
		m_Renderer.SetBackground(Scenes[m_CurScene]->GetBackground());
		Scenes[m_CurScene]->ShowScene();
		return true;
	}
	return false;
}

bool SceneManager::CheckQuitNextUpdate()
{
	return m_IsQuittingNextUpdate;
}

void SceneManager::Update(float a_Dt)
{
	//this is just a shell to update the scene, and the only scene that needs updating is the game scene
	Scenes[m_CurScene]->Update(a_Dt);
}

void SceneManager::SetInputHandler(InputHandler* a_pInputHandler)
{
	m_pInputHandler = a_pInputHandler;
}

InputHandler* SceneManager::GetInputHandler()
{
	return m_pInputHandler;
}
