#include "stdafx.h"
#include "BoardFeatures.hpp"
#include "PawnTexture.hpp"

std::vector<std::shared_ptr<GameObject>> BoardFeatures::AvailableFieldsFrames;
std::shared_ptr<GameObject> BoardFeatures::pawnShadow;

//std::shared_ptr<sf::Texture> BoardFeatures::frameTexture;
sf::Texture* BoardFeatures::frameTexture;

const std::string BoardFeatures::frameTexture_filename{ "images/field_contour.png" };


void BoardFeatures::Init()
{
	initFrameTexture();

	//initPawnShadow();

}

void BoardFeatures::SetPawnShadow(Field * field, FieldState PlayerIndex)
{
	BoardFeatures::pawnShadow->setPosition(field->getPosition() + field->getSize() / 2.0f);
	if (PlayerIndex == FieldState::p1)
	{
		BoardFeatures::pawnShadow->setTexture(PawnTexture::blackPawn);
	}
	else
	{
		BoardFeatures::pawnShadow->setTexture(PawnTexture::whitePawn);
	}

}

void BoardFeatures::SetAvailableFieldsFrames(const std::vector<Field*>& AvailableFields)
{
	AvailableFieldsFrames.clear();

	for (Field* field : AvailableFields)
	{
		// Emplacing a new field frame pointer based on the iterated field
		AvailableFieldsFrames.emplace_back(BoardFeatures::NewFieldFrame(field));
	}

}

void BoardFeatures::Clear()
{
	AvailableFieldsFrames.clear();
	delete frameTexture;
}

void BoardFeatures::initPawnShadow()
{
	pawnShadow = std::shared_ptr<GameObject>(new GameObject);
	// Setting proper color so that the object is transparent
	pawnShadow->setColor(sf::Color(255, 255, 255, 127));

	pawnShadow->setSize(sf::Vector2f(Pawn::getPawnSize(), Pawn::getPawnSize()));
	pawnShadow->setTexture(PawnTexture::blackPawn);
	pawnShadow->setOriginToCenter();

}

void BoardFeatures::initFrameTexture()
{
	//frameTexture = std::shared_ptr<sf::Texture>(new sf::Texture);
	frameTexture = new sf::Texture;
	// Loading texture of the field frame from the file
	frameTexture->loadFromFile(frameTexture_filename);
}

std::shared_ptr<GameObject> BoardFeatures::NewFieldFrame(Field * field)
{
	// Creating a new shared pointer to a field frame
	std::shared_ptr<GameObject> fieldFrame(new GameObject(frameTexture));

	// Setting its size and proper position
	fieldFrame->setSize(field->getSize());

	fieldFrame->setPosition(field->getPosition() + field->getSize() / 2.f);

	fieldFrame->setOriginToCenter();

	return fieldFrame;
}
