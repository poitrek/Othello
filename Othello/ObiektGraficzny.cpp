#include "stdafx.h"
#include "ObiektGraficzny.h"


ObiektGraficzny::ObiektGraficzny()
{
}

ObiektGraficzny::~ObiektGraficzny()
{
}

void ObiektGraficzny::setSize(sf::Vector2f vec)
{
	float scaleX = vec.x / sprite.getTexture()->getSize().x;
	float scaleY = vec.y / sprite.getTexture()->getSize().y;
	//std::cout << "scaleXY: " << scaleX << " " << scaleY << std::endl;
	sprite.setScale(scaleX, scaleY);
}

sf::Vector2f ObiektGraficzny::getSize()
{
	return { sprite.getScale().x * texture.getSize().x, sprite.getScale().y * texture.getSize().y };
}
void ObiektGraficzny::setPosition(sf::Vector2f vec)
{
	sprite.setPosition(vec);
}
sf::Vector2f ObiektGraficzny::getPosition()
{
	return sprite.getPosition();
}

void ObiektGraficzny::draw(sf::RenderWindow &window)
{
	window.draw(this->sprite);
}
/*
void ObiektGraficzny::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(this->sprite, state);
}
*/