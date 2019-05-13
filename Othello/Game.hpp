#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Renderer.hpp"

class Game
{
public:

	Engine engine;

	View view;



	sf::RenderWindow window;

	SideMenu sideMenu;

	enum GameState
	{
		Playing,
		Over
	}static State;

	bool isExiting;

	// Main function that consists of initialization, game loop and clearing
	void Run();

	// Initialazing the game including textures, sprites, game setup
	void Init();

	// The main loop of the game that repeats until it's closed
	void GameLoop();

	// Clearing objects of the program that've been dynamically allocated
	void Clear();

};

