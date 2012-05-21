#include "Renderer.hpp"
#include "WindowManager.hpp"
#include "GUIManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Renderer::Renderer(GUIManager& a_guiMgr, WindowManager& a_WindowMgr)
:	m_WindowMgr(a_WindowMgr)
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
	if(m_pBackgroundImage)
		renderWindow.draw(*m_pBackgroundImage);

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
