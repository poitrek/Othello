#include "stdafx.h"
#include "Board.h"
#include <iostream>


Board::Board(sf::Vector2f pos)
{
	if (!texture.loadFromFile(file_name))
	{
		std::cout << "Error [Board::Board()]: nie udalo sie otworzyc pliku " << file_name << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 520, 520)); // domyœlne (500, 500)
	sprite.setPosition(pos.x, pos.y);
}


Board::~Board()
{
}


sf::Vector2f Board::getSize()
{
	//return { sprite.getScale().x * texture.getSize().x, sprite.getScale().y * texture.getSize().y };
	return { 520.0f, 520.0f };
}
