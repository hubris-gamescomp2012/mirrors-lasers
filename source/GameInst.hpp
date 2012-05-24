#ifndef GAME_INST_HPP
#define GAME_INST_HPP

#include "Scene.hpp"
#include "ResourceManager.hpp"

#include "Defs.hpp"

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Notebook.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/Label.hpp>

#include <chipmunk\chipmunk.h>

class Block;
class Renderer;
class Player;
class Cursor;
class Emitter;
class GameObject;
class Catcher;

namespace sf
{
	class Sprite;
}

class GameInst : public Scene
{
public:
	GameInst(GUIManager& a_GUIMgr, ResourceManager& a_ResMgr, Renderer& a_Renderer);
	bool Start();
	void Stop();
	void LoadLevel();
	void UnloadLevel();
	virtual void Update(float a_dt);
	virtual void UpdateGUISizes();
	//
	sfg::Button::Ptr m_pQuitMenuButton;
	//
	void SetCursor(Cursor* a_pNewCursor);
	//
private:
	Player* m_pPlayer;
	Cursor* m_pCursor;
	std::vector<Block*> m_blocks;
	std::vector<Emitter*> Emitters;
	std::vector<Catcher*> Catchers;
	bool m_Running;
	Renderer& m_Renderer;
	ResourceManager& m_ResMgr;
	//
	float m_tLeftPhysUpdate;
	//
	cpSpace* m_pSpace;	//chipmunk physworld
	StaticRigidQuad m_WorldBounds;	//world boundaries
	//
	std::vector<sf::Vector2f> catcherPositions;
	float laserRotation;
	bool m_won;
	float m_winTimer;
	sfg::Image::Ptr m_winImage;
	sf::Image m_winImageSource;
};

#endif	//GAME_INST_HPP