#pragma once
#include "GameObject.h"
class Board : public GameObject
{
private:
	const std::string file_name = "../Othello/Board texture.jpg";
	
public:
	Board(sf::Vector2f pos);
	~Board();

	sf::Vector2f getSize();
};

