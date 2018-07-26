#pragma once
#include "ObiektGraficzny.h"
class Board : public ObiektGraficzny
{
private:
	const std::string file_name = "../Othello/Board texture.jpg";
	
public:
	Board(sf::Vector2f pos);
	~Board();

	sf::Vector2f getSize();
};

