#include "GUIManager.hpp"
#include "WindowManager.hpp"

//#include <SFGUI/SFGUI.hpp>
//#include <SFML/Graphics/Drawable.hpp>
//#include <SFGUI/Desktop.hpp>

GUIManager::GUIManager(WindowManager& a_WindowMgr)
//:	m_sfgui()
//,	m_Desktop()
:	m_WindowMgr(a_WindowMgr)
{
	//
}

void GUIManager::Update(float a_Dt)
{
	//m_Desktop.Update(a_Dt);
}

void GUIManager::RenderGui(sf::RenderWindow& a_RenderWindow)
{
	//m_sfgui.Display(a_RenderWindow);
}

/*void GUIManager::CreateTestWindow()
{
	// Create a test window to show sfgui works
	//sfg::Window::Ptr window( sfg::Window::Create() );
	//m_Desktop.Add(window);
	window->SetTitle( "new window" );

	// Widgets.
	sfg::Button::Ptr destroy_button( sfg::Button::Create( "Destroy" ) );
	sfg::Button::Ptr front_button( sfg::Button::Create( "Main window to front" ) );

	// Layout.
	sfg::Box::Ptr box( sfg::Box::Create( sfg::Box::VERTICAL, 5.f ) );
	box->Pack( sfg::Label::Create( "This is a newly created window, from runtime, interactively." ), false );
	box->Pack( sfg::Label::Create( "You can move me around, try it!" ), false );
	box->Pack( sfg::Label::Create( "Or click the button below to destroy me. :-(" ), false );
	box->Pack( destroy_button, false );
	box->Pack( front_button, false );
	
	window->Add( box );
	//m_Desktop.Add( window );
	//m_Desktop.SetProperty( "Button#create_window > Label", "FontSize", 18.f );

	// Signals.
	//destroy_button->OnLeftClick.Connect( &DesktopExample::OnDestroyWindowClick, this );
	//front_button->OnLeftClick.Connect( &DesktopExample::OnFrontClick, this );
	//
}*/

void GUIManager::HandleEvent(sf::Event a_Event)
{
	//m_Desktop.HandleEvent(a_Event);
}

/*void GUIManager::AddWidget(sfg::SharedPtr<sfg::Widget> a_Widget)
{
	m_Desktop.Add(a_Widget);
}*/

/*sfg::Desktop& GUIManager::GetDesktop()
{
	return m_Desktop;
}*/

sf::Vector2f GUIManager::GetWindowDim()
{
	return m_WindowMgr.GetWindowDim();
}
