#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf
{
	class Image;
	class Sprite;
	class Texture;
};

class Anim;

class ResourceManager
{
public:
	ResourceManager();
	//
	bool LoadSFMLImage(std::string FilePath, _Out_ sf::Image** Out = NULL );
	bool LoadSFMLTexture(std::string FilePath, _Out_ sf::Texture** Out = NULL );
	bool CreateSprite(std::string FilePath, _Out_ sf::Sprite** a_ppOut = NULL );	// _In_ sf::Rect<int>* a_pSubRect = NULL
	bool CreateAnim(std::string FilePath, sf::Vector2f a_FrameSize, double FrameLength, short numFrames, _Out_ Anim** a_ppOut = NULL );
	//
private:
	//
	std::vector< std::pair<std::string, sf::Image*> > Images;
	std::vector< std::pair<std::string, sf::Texture*> > Textures;
	std::vector< std::pair<std::string, sf::Sprite*> > Sprites;
};

#endif	//RESOURCE_MANAGER_HPP