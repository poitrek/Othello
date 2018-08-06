// Othello.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <windows.h>
#include "GameObject.h"
#include "Board.h"
#include "Field.h"
#include "Pawn.h"
#include "SideMenu.h"
#include "Engine.hpp"
#include "Creator.hpp"
#include "Renderer.hpp"
#include "MouseHandler.hpp"


/*
This is the master branch of the project that
will be expanded with new ideas, eg. a computer
opponent in the game, etc.
*/


std::ostream & operator << (std::ostream &ostr, State state)
{
	switch (state)
	{
	case p1:
		ostr << "p1";
		break;
	case p2:
		ostr << "p2";
		break;
	case none:
		ostr << "[None]";
		break;
	}
	return ostr;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	///Engine engine;
	sf::RenderWindow window;// domyślne (780, 510)
	window.create(sf::VideoMode(840, 520), "Othello", sf::Style::Close);

	Renderer::AddLayers(3);


	Board board({ 0.0f, 0.0f });
	SideMenu sideMenu;
	std::vector <Field*> FieldVector;
	std::vector <Pawn*> PawnVector;  // Wektor przechowujący adresy wszystkich pionków
	

	Creator::DrawFields(board, Engine::FieldTab); // Procedura rysująca nam wszystkie pola

	FieldVector = Creator::SetFieldVector(Engine::FieldTab);
	
	Creator::CreateSideMenu(sideMenu, window, board); // Procedura rysująca menu boczne
	
	Creator::FirstPawns(PawnVector, Engine::FieldTab); // Procedura tworząca 4 startowe pionki
	
	Engine::UpdateAvailableFields(FieldVector); // Początkowy update pól


	Renderer::Add(&board, 1);
	Renderer::Add(&sideMenu, 1); 
	
	Field::setPawnShadow();

	
	while (window.isOpen())//=================//
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				MouseHandler::mouseReleased = true;
				break;
			}
		}

		
		// Updates the mouse position
		MouseHandler::update(window);

		// Reacts to hovering an available field with mouse
		Engine::HandleMouseHover(FieldVector, window);

		// Reacts to clicking an available field by the player
		Engine::HandlePlayerMove(FieldVector, PawnVector, sideMenu, window);
		
		
		sideMenu.update_clock_message1();


		// -------- The rendering section --------

		window.clear(sf::Color(140, 112, 60)); // Clearing the window
		
		Renderer::DrawAll(window);

		window.display();



	}//=======================================//

	Renderer::Clear();
	FieldVector.clear();
	PawnVector.clear();
	Engine::Clear();

    return 0;
}

