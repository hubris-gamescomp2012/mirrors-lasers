#include "GameInst.hpp"
#include "GUIManager.hpp"
#include "Helpers.hpp"

GameInst::GameInst(GUIManager& a_GUIMgr)
:	Scene(a_GUIMgr)
,	m_Running(false)
//,	m_pQuitMenuButton(sfg::Button::Create("Quit to Main Menu"))
	//
{
	//grab the screen dimensions
	sf::Vector2f windowDim = m_GUIMgr.GetWindowDim();

	//to handle button presses and the like
	m_pSelectListener = new SelectListener(*this);
	
	/** Create Adjustment.
		* @param value Current value.
		* @param lower Minimum value.
		* @param upper Maximum value.
		* @param minor_step Minor change value (such as clicking on arrow button).
		* @param major_step Major change value (such as clicking on the scroll area).
		* @param page_size Page size (how many entries are visible / slider size).
		* @return Adjustment.
		*/

	//add a systemlist scrollbar
	/*sfg::Scrollbar::Ptr systemScrollBar = sfg::Scrollbar::Create(sfg::Scale::VERTICAL);
	m_pSystemList->Attach(systemScrollBar, sf::Rect<unsigned int>(1,1,1,1), 0, 0);
	sfg::Adjustment::Ptr adjustment = systemScrollBar->GetAdjustment();
	systemScrollBar->SetRequisition( sf::Vector2f( 0.f, windowDim.y/2 ) );

	// Tune the adjustment parameters.
	adjustment->SetLower( 20.f );
	adjustment->SetUpper( 100.f );

	// How much it should change when clicked on the stepper.
	adjustment->SetMinorStep( 1.f );

	// How much it should change when clicked on the trough.
	adjustment->SetMajorStep( 5.f );*/

	//setup gui
	sf::FloatRect allocRect;
	//double invHeightScalar = 10;
	//double invWidthScalar = 5;
	
	//quit to menu button
	//sfg::Context::Get().GetEngine().SetProperty("Button", "FontSize", 20.0f);
	/*m_pQuitMenuButton->SetRequisition( sf::Vector2f(windowDim.x / 20, windowDim.y / 20) );
	allocRect = m_pQuitMenuButton->GetAllocation();
	m_pQuitMenuButton->SetPosition( sf::Vector2f(5, 5) );
	m_pQuitMenuButton->Show(false);
	m_GUIMgr.AddWidget(m_pQuitMenuButton);
	Widgets.push_back(m_pQuitMenuButton);*/
}

bool GameInst::Start()
{
	m_Running = true;
	return true;
}

void GameInst::Stop()
{
	m_Running = false;
	//
}

void GameInst::Update(float a_dt)
{
	if(m_Running)
	{
		//
	}
}

void GameInst::UpdateGUISizes()
{
	//
}

void GameInst::Select(void* a_pSelectee, SelectListener::Type a_SelectedType)
{
	//
}
