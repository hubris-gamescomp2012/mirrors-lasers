#include "SceneManager.hpp"
#include "GameInst.hpp"

#include <iostream>

void SceneManager::GotoGameScene()
{
	EnableSceneByID(SCENE_GAMEINST);
	m_pGameInst->Start();
}

void SceneManager::GotoOptionsScene()
{
	//
}

void SceneManager::Quit()
{
	m_IsQuittingNextUpdate = true;
}

void SceneManager::GotoMenuScene()
{
	m_pGameInst->Stop();
	EnableSceneByID(SCENE_MAINMENU);
}
