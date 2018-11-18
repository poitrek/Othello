#include "stdafx.h"
#include "Field.h"
#include <iostream>

extern sf::Texture *texture_w;
extern sf::Texture *texture_b;
extern void tex_setup();

const std::string Field::file_name = "../Othello/Pole.jpg";
sf::Texture* Field::texture;
float Field::fieldSize;

int Field::_ref_count{ 0 };

Field::Field()
{
	_ref_count++;

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

Field::~Field()
{
	_ref_count--;
	if (_ref_count == 0)
	{
		delete pawnShadow;
	}
}


sf::Vector2f Field::getSize()
{
	return { sprite.getScale().x * texture->getSize().x, sprite.getScale().y * texture->getSize().y };
}

void Field::SetState(FieldState _state)
{
	this->state = _state;
	if (pawn != nullptr)
		pawn->Set(_state);
}

void Field::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}


//std::shared_ptr<GameObject> Field::pawnShadow(nullptr);
GameObject* Field::pawnShadow(nullptr);


void Field::setPawnShadow()
{
	//pawnShadow = std::shared_ptr<GameObject>(new GameObject);
	pawnShadow = new GameObject;
	sf::Sprite *spr = pawnShadow->getSprite();
	//tex_setup();
	spr->setTexture(*texture_b); // tylko tymczasowo
	pawnShadow->setOriginToCenter();
	pawnShadow->setSize(sf::Vector2f(Pawn::getPawnSize(), Pawn::getPawnSize()));
	spr->setColor(sf::Color(255, 255, 255, 127));

	Field::updatePawnShadow(p1);
	
}

void Field::updatePawnShadow(FieldState curPlayer)
{
	switch (curPlayer)
	{
	case p1:
		pawnShadow->setTexture(texture_b);
		break;
	case p2:
		pawnShadow->setTexture(texture_w);
		break;
	}
}

void Field::setPawnShadowPosition(Field *field)
{
	pawnShadow->setPosition(field->getPosition() + field->getSize() / 2.0f);
}
