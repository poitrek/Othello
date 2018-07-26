#include "stdafx.h"
#include "Field.h"
#include <iostream>

extern sf::Texture *texture_w;
extern sf::Texture *texture_b;
extern void tex_setup();

const std::string Field::file_name = "../Othello/Pole.jpg";
sf::Texture* Field::texture;

Field::Field()
{
	if (texture == nullptr)
	{
		texture = new sf::Texture;
		if (!texture->loadFromFile(file_name))
		{
			std::cout << "Error [Board::Board()]: nie udalo sie otworzyc pliku " << file_name << std::endl;
		}
	}

	texture->setSmooth(true);
	sprite.setTexture(*texture);
	sprite.setScale(scaleFactor, scaleFactor);
	sprite.setPosition({ 20, 20 });
	state = none;
	this->pawn = nullptr;
}

Field::Field(sf::Vector2f pos = { 20.0f, 20.0f }) // Nieu¿ywany
{
	if (texture == nullptr)
	{
		texture = new sf::Texture;
		if (!texture->loadFromFile(file_name))
		{
			std::cout << "Error [Board::Board()]: nie udalo sie otworzyc pliku " << file_name << std::endl;
		}
	}
	sprite.setTexture(*texture);
	//sprite.setScale(0.25, 0.25);
	sprite.setPosition(pos);
}


Field::~Field()
{	
}

sf::Vector2f Field::getSize()
{
	return { sprite.getScale().x * texture->getSize().x, sprite.getScale().y * texture->getSize().y };
}

void Field::Set(State _state)
{
	this->state = _state;
	if (pawn != nullptr)
		pawn->Set(_state);
}

void Field::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

sf::Sprite Field::pawnShadow;

void Field::setPawnShadow(float pawnSize)
{
	tex_setup();
	pawnShadow.setTexture(*texture_b); // tylko tymczasowo
	pawnShadow.setOrigin(pawnShadow.getTexture()->getSize().x / 2.0f, pawnShadow.getTexture()->getSize().y / 2.0f);
	setSpriteSize(pawnShadow, sf::Vector2f(pawnSize, pawnSize));
	pawnShadow.setColor(sf::Color(255, 255, 255, 127)); // przezroczysty	
}

void Field::updatePawnShadow(State curPlayer)
{
	switch (curPlayer)
	{
	case p1:
		pawnShadow.setTexture(*texture_b);
		break;
	case p2:
		pawnShadow.setTexture(*texture_w);
		break;
	}
}

void Field::setPawnShadowPosition()
{
	pawnShadow.setPosition(getPosition() + getSize() / 2.0f);
}

void Field::Highlight(State curPlayer, float pawnSize)
{	
	sprite.setColor(sf::Color(255, 255, 255, 190));
}

void Field::Standard()
{	
	sprite.setColor(sf::Color(255, 255, 255));
}
