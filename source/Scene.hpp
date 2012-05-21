#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
//#include <SFGUI/SharedPtr.hpp>

namespace sf
{
	class Sprite;
};

/*namespace sfg
{
	class SFGUI;
	class Widget;
};*/

class Button;
class Entity;
class SpeechBubble;
class Anim;
class GUIManager;

class Scene
{
public:
	Scene(GUIManager& a_GUIMgr);
	~Scene();
	virtual void Update(float a_dt)=0;
	virtual void UpdateGUISizes()=0;
	//
	void SetBackground( _In_ sf::Sprite* a_pBGImage );
	sf::Sprite* GetBackground();
	//
	virtual void ShowScene();
	virtual void HideScene();
	//
protected:
	GUIManager& m_GUIMgr;
	//
	sf::Sprite* m_pBackgroundImage;
	//std::vector< sfg::SharedPtr<sfg::Widget> > Widgets;
};

#endif