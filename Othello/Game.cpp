#include "stdafx.h"
#include "Game.hpp"

Game::GameState Game::State{ Game::Playing };

//Engine Game::engine;

//sf::RenderWindow Game::window;

void Game::Run()
{
	Init();

	while (!isExiting)
	{
		GameLoop();
	}

	Clear();

}

void Game::Init()
{
	isExiting = false;

	window.create(sf::VideoMode(840, 520), "Othello", sf::Style::Close);




}

void Game::GameLoop()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			// Important!
			isExiting = true;
			break;
		
		default:
			break;
		}
	}




	window.clear(sf::Color(140, 112, 60));

	window.display();
}

void Game::Clear()
{
}
