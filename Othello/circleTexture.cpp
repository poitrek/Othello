#include "stdafx.h"
#include "circleTexture.h"

const std::string file_name_b = "../Othello/black_circle.png";
const std::string file_name_w = "../Othello/white_circle.png";

sf::Texture *texture_b;// = new sf::Texture;
sf::Texture *texture_w;//= new sf::Texture;


void setSpriteSize(sf::Sprite &sprite, sf::Vector2f vec)
{
	float scaleX = vec.x / sprite.getTexture()->getSize().x;
	float scaleY = vec.y / sprite.getTexture()->getSize().y;
	sprite.setScale(scaleX, scaleY);
}

void tex_setup()
{
	if (texture_b == nullptr)
		texture_b = new sf::Texture;
	if (texture_w == nullptr)
		texture_w = new sf::Texture;
	if (!texture_b->loadFromFile(file_name_b))
	{
		std::cout << "Error [circleTexture::setup()]: nie udalo sie otworzyc pliku " << file_name_b << std::endl;
	}
	if (!texture_w->loadFromFile(file_name_w))
	{
		std::cout << "Error [circleTexture::setup()]: nie udalo sie otworzyc pliku " << file_name_w << std::endl;
	}
}
