#include "stdafx.h"
#include "Pawn.h"
#include "Field.h"
#include <iostream>
#include <cmath>

const std::string Pawn::file_name_b = "../Othello/black_circle.png";
const std::string Pawn::file_name_w = "../Othello/white_circle.png";
sf::Texture* Pawn::texture_b;
sf::Texture* Pawn::texture_w;
float Pawn::pawnSize;

Pawn::Pawn(Field &F, State playerIndex)
{
	
	switch (playerIndex)
	{
	case p1:
		sprite.setTexture(*texture_b);
		break;
	case p2:
		sprite.setTexture(*texture_w);
		break;
	}
	//std::cout << pawnSize << std::endl;
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);
	setSize(sf::Vector2f{ pawnSize, pawnSize });
	// Uffffff....
	
	//std::cout << "Origin: " << sprite.getOrigin().x << " " << sprite.getOrigin().y << std::endl;
	sf::Vector2f fPos = F.sprite.getPosition() + F.getSize() / 2.0f;
	//std::cout << "fPos: " << fPos.x << ", " << fPos.y << std::endl;
	//std::cout << "round(fPos): " << round(fPos.x) << ", " << round(fPos.y) << std::endl;
	sprite.setPosition({ round(fPos.x), round(fPos.y) });
	F.Set(playerIndex);  // Nadajemy ju¿ temu polu odpowiedni indeks
	F.pawn = this;  // I przekazujemy temu polu adres tego pionka
}

Pawn::~Pawn()
{	
}

void Pawn::Place(std::vector<Pawn*> pawnTab)
{
	pawnTab.push_back(this);
	Renderer::Add(this, 3);
}

void Pawn::setTextures()
{
	texture_b = new sf::Texture;
	texture_w = new sf::Texture;
	if (!texture_b->loadFromFile(this->file_name_b))
	{
		std::cout << "Error [Pawn::Pawn()]: nie udalo sie otworzyc pliku " << this->file_name_b << std::endl;
	}
	if (!texture_w->loadFromFile(this->file_name_w))
	{
		std::cout << "Error [Pawn::Pawn()]: nie udalo sie otworzyc pliku " << this->file_name_w << std::endl;
	}
	texture_b->setSmooth(true);
	texture_w->setSmooth(true);
}

void Pawn::Set(State playerIndex)
{
	switch (playerIndex)
	{
	case p1:
		sprite.setTexture(*texture_b);
		break;
	case p2:
		sprite.setTexture(*texture_w);
		break;
	}
	return;
}

float Pawn::getPawnSize()
{
	return Pawn::pawnSize;
}
