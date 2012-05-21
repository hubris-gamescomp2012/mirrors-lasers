#include "SceneManager.hpp"
#include "GameInst.hpp"

#include <iostream>

void SceneManager::GotoGameScene()
{
	m_pGameInst->Start();
	EnableSceneByID(SCENE_GAMEINST);
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
