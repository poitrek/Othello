#include "stdafx.h"
#include "PawnTexture.hpp"

sf::Texture* PawnTexture::blackPawn{ nullptr };
sf::Texture* PawnTexture::whitePawn{ nullptr };

const std::string PawnTexture::filename_blackPawn{ "../Othello/black_circle.png" };
const std::string PawnTexture::filename_whitePawn{ "../Othello/white_circle.png" };

void PawnTexture::Init()
{
	if (blackPawn == nullptr)
	{
		blackPawn = new sf::Texture;
	}
	if (whitePawn == nullptr)
	{
		whitePawn = new sf::Texture;
	}
	if (!blackPawn->loadFromFile(filename_blackPawn))
	{
		std::cout << "Error [circleTexture::setup()]: nie udalo sie otworzyc pliku " << filename_blackPawn << std::endl;
	}
	if (!whitePawn->loadFromFile(filename_whitePawn))
	{
		std::cout << "Error [circleTexture::setup()]: nie udalo sie otworzyc pliku " << filename_whitePawn << std::endl;
	}
}

void PawnTexture::Clear()
{
	delete whitePawn;
	delete blackPawn;
}
