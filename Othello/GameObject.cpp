#include "stdafx.h"
#include "GameObject.h"


int GameObject::number_of_objects{ 0 };


GameObject::GameObject()
{
	//this->set_id();
}

GameObject::GameObject(sf::Texture * txtr)
{
	//this->set_id();
	this->texture = *txtr;
	this->sprite.setTexture(texture);
}

void GameObject::setTexture(sf::Texture * txtr)
{
	this->texture = *txtr;
	this->sprite.setTexture(texture);
}

void GameObject::setSize(sf::Vector2f vec)
{
	float scaleX = vec.x / sprite.getTexture()->getSize().x;
	float scaleY = vec.y / sprite.getTexture()->getSize().y;
	//std::cout << "scaleXY: " << scaleX << " " << scaleY << std::endl;
	sprite.setScale(scaleX, scaleY);
}

sf::Vector2f GameObject::getSize()
{
	return { sprite.getScale().x * texture.getSize().x, sprite.getScale().y * texture.getSize().y };
}
void GameObject::setPosition(sf::Vector2f vec)
{
	sprite.setPosition(vec);
}
sf::Vector2f GameObject::getPosition()
{
	return sprite.getPosition();
}

void GameObject::setOriginToCenter()
{
	sf::Vector2u texsize = sprite.getTexture()->getSize();
	sprite.setOrigin(texsize.x * 0.5f, texsize.y * 0.5f);
}

void GameObject::setColor(const sf::Color &color)
{
	this->sprite.setColor(color);
}

void GameObject::draw(sf::RenderTarget &target)
{
	target.draw(this->sprite);
}
int GameObject::GetObjectId()
{
	return object_id;
}
int GameObject::GetNumberOfObjects()
{
	return number_of_objects;
}
void GameObject::set_id()
{
	number_of_objects++;

	this->object_id = number_of_objects;
}
/*
void GameObject::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(this->sprite, state);
}
*/