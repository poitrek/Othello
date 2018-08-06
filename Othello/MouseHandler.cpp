#include "stdafx.h"
#include "MouseHandler.hpp"

sf::Vector2i MouseHandler::currentPos{ 0, 0 };
sf::Vector2i MouseHandler::previousPos{ 0, 0 };
sf::Vector2i MouseHandler::d_Pos{ 0, 0 };

bool MouseHandler::mouseReleased{ false };

MouseHandler::MouseState MouseHandler::state{ MouseHandler::_passive };


void MouseHandler::update(sf::RenderWindow &window)
{
	currentPos = sf::Mouse::getPosition(window);
}

bool MouseHandler::mouseHovered(GameObject *obj, sf::RenderTarget &target)
{
	sf::Vector2f gPos = obj->getPosition();
	sf::Vector2f gSize = obj->getSize();
	
	return (currentPos.x > gPos.x && currentPos.x < gPos.x + gSize.x &&
		currentPos.y > gPos.y && currentPos.y < gPos.y + gSize.y);
}

bool MouseHandler::mouseClicked(GameObject & obj, sf::RenderTarget &target)
{
	return (mouseHovered(&obj, target) && singleClick(sf::Mouse::Left));
}

bool MouseHandler::singleClick(sf::Mouse::Button btn)
{
	bool ret;
	///currentPos = sf::Mouse::getPosition();

	int d_Poslength;

	switch (state)
	{
	case MouseHandler::_passive:
		ret = false;

		if (sf::Mouse::isButtonPressed(btn))
		{
			mouseReleased = false;
			state = _held;
		}
		break;

	case MouseHandler::_held:
		ret = false;

		// Sprawdzamy, czy mysz zosta³a znacz¹co przekroczona
		d_Pos = currentPos - previousPos;
		d_Poslength = abs(d_Pos.x) + abs(d_Pos.y);

		if (d_Poslength > 2)
		{
			state = _moved;
			break;
		}
		
		if (mouseReleased)
		{
			state = _released;
		}

		break;

	case MouseHandler::_released:
		ret = true;
		state = _passive;
		break;

	case MouseHandler::_moved:
		ret = false;
		if (mouseReleased)
		{
			state = _passive;
		}

		break;

	default:
		break;
	}

	previousPos = currentPos;
	return ret;
}
