#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class MouseHandler
{
public:
	static bool mouseReleased;


	static void update(sf::RenderWindow &window);

	// The sf::RenderTarget &target parameter is probably unnecessary
	// Previously: 
	//bool MouseHandler::mouseHovered(GameObject *obj, sf::RenderTarget &target);
	static bool mouseHovered(GameObject *obj);

	static bool mouseClicked(GameObject &obj);

	static bool singleClick(sf::Mouse::Button btn);

private:
	static sf::Vector2i currentPos;
	static sf::Vector2i previousPos;
	static sf::Vector2i d_Pos;

	enum MouseState
	{
		_passive,
		_held,
		_released,
		_moved
		
	};
	static MouseState state;

};

