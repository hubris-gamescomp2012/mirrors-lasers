#include "Renderer.hpp"
#include "WindowManager.hpp"
#include "GUIManager.hpp"
#include "ResourceManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics.hpp>

Renderer::Renderer(GUIManager& a_guiMgr, WindowManager& a_WindowMgr, ResourceManager& a_ResMgr)
:	m_WindowMgr(a_WindowMgr)
,	m_ResMgr(a_ResMgr)
,	m_pBackgroundImage(NULL)
,	m_guiMgr(a_guiMgr)
{
	//
}

bool Renderer::Init()
{
	//
	return true;
}

bool Renderer::Render(float a_dt)
{
	//sf::RenderTarget& renderTarget = m_WindowMgr.GetRenderTarget();
	sf::RenderWindow& renderWindow = m_WindowMgr.GetRenderWindow();
	
	//update the gui
	m_guiMgr.Update(a_dt);

	//clear screen
	renderWindow.clear();

	//first, draw the background image if there is one
	/*if(m_pBackgroundImage)
		renderWindow.draw(*m_pBackgroundImage);*/

	//render sprites
	for(auto it = VisibleSprites.begin(); it != VisibleSprites.end(); it++ )
	{
		sf::Sprite* sprite = *it;
		renderWindow.draw(*sprite);
	}

	//render the gui
	m_guiMgr.RenderGui(renderWindow);

	//display the screen
	m_WindowMgr.Display(a_dt);
	return false;
}

bool Renderer::CleanUp()
{
	//
	return true;
}

void Renderer::SetBackground( _In_ sf::Sprite* a_pBG )
{
	m_pBackgroundImage = a_pBG;
}

sf::Vector2f Renderer::GetWindowDim()
{
	return m_WindowMgr.GetWindowDim();
}

void Renderer::AddDrawableSprite(sf::Sprite* a_pSprite)
{
	VisibleSprites.push_back(a_pSprite);
}

void Renderer::RemoveDrawableSprite(sf::Sprite* a_pSprite)
{
	for(auto it = VisibleSprites.begin(); it != VisibleSprites.end(); it++ )
	{
		//if((*it)->)
	}
}
