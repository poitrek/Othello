#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Renderer.hpp"

class Game
{
public:

	Engine engine;


	sf::RenderWindow window;

	enum GameState
	{
		Playing,
		Over
	}static State;

	bool isExiting;

	void Run();

	void Init();

	void GameLoop();

	void Clear();

};

