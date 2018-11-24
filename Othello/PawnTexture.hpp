#pragma once
#include <SFML/Graphics.hpp>

class PawnTexture
{
	static const std::string filename_blackPawn;
	static const std::string filename_whitePawn;

public:
	static sf::Texture* whitePawn;
	static sf::Texture* blackPawn;

	static void Init();
	static void Clear();

};

