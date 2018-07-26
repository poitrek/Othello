// Othello.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <windows.h>
#include "ObiektGraficzny.h"
#include "Board.h"
#include "Field.h"
#include "Pawn.h"
#include "SideMenu.h"
#include "fieldLogic.h"

bool cursorEntered(Field &field, float posX, float posY)
{
	float top = field.getPosition().y;
	float bottom = field.getPosition().y + field.getSize().y;
	float left = field.getPosition().x;
	float right = field.getPosition().x + field.getSize().x;

	return posY < bottom && posY > top && posX > left && posX < right;
}
bool cursorEntered(Field &field, sf::Vector2f pos)
{
	float top = field.getPosition().y;
	float bottom = field.getPosition().y + field.getSize().y;
	float left = field.getPosition().x;
	float right = field.getPosition().x + field.getSize().x;

	return pos.y < bottom && pos.y > top && pos.x > left && pos.x < right;
}

void setup_DrawFields(Board &board, Field field[][8], float &fieldSize)
{
	State s = none;
	//sf::Vector2f fieldSize = field[0][0].getSize();
	sf::Vector2f posBuf{ 12.0f, 12.0f };

	fieldSize = (board.getSize().x - 2 * posBuf.x) / 8.0f; // Odpowiedni rozmiar pola dostosowany do rozmiarów planszy
	std::cout << board.getSize().x << ", " << board.getSize().y << std::endl;
	std::cout << fieldSize << std::endl;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			field[i][j].setX(i); field[i][j].setY(j);
			field[i][j].setSize({ fieldSize, fieldSize }); // Nastawiamy rozmiar pola na ten właściwy
			field[i][j].setPosition(board.getPosition().x + posBuf.x + i*fieldSize, board.getPosition().y + posBuf.y + j*fieldSize); // i konsekwentną pozycję
		}
	std::cout << field[0][0].getSize().x << ", " << field[0][0].getSize().y << std::endl;

}
void setup_DrawSideMenu(SideMenu& sideMenu, sf::RenderWindow& window, Board& board)
{
	const float posBuf1 = 5.0f;
	const float posBuf2 = 5.0f;
	const float posBuf3 = 20.0f;
	sf::Vector2f pos;
	pos.x = board.getPosition().x + board.getSize().x + posBuf1;
	pos.y = posBuf2;
	sideMenu.setPosition(pos);
	float width = window.getSize().x - pos.x - posBuf2;
	float height = window.getSize().y - posBuf2 - posBuf3;
	sideMenu.setSize({ width, height });
	sideMenu.setLabels();
}
void setup_FirstPawns(std::vector<Pawn*> &PawnTab, Field field[][8], float pawnSize)
{
	Pawn *veryFirst = new Pawn;
	veryFirst->setTextures();

	Pawn *pawn1 = new Pawn(field[3][3], p2, pawnSize);
	Pawn *pawn2 = new Pawn(field[3][4], p1, pawnSize);
	Pawn *pawn3 = new Pawn(field[4][3], p1, pawnSize);
	Pawn *pawn4 = new Pawn(field[4][4], p2, pawnSize);

	PawnTab.push_back(pawn1);
	PawnTab.push_back(pawn2);
	PawnTab.push_back(pawn3);
	PawnTab.push_back(pawn4);

	delete veryFirst;
}
void setup_FillFieldTab(std::vector<Field*> &FieldTab, Field field[][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			FieldTab.push_back(&field[i][j]);
}

void ChangePlayer(State& curPlayer)
{
	if (curPlayer == p1)
	{
		curPlayer = p2;
		return;
	}
	if (curPlayer == p2)
	{
		curPlayer = p1;
		return;
	}
}
void UpdateAvailableFields(std::vector<Field*> &FieldTab, Field field[][8], State curPlayer)
{
	for (Field *F : FieldTab)
		if (F->Get() != none)
			F->Available = false;
		else
			if (isMoveValid(field, F, curPlayer))
				F->Available = true;
			else
				F->Available = false;
}
bool IsAnyMoveAvailable(std::vector<Field*> &FieldTab)
{
	for (Field *F : FieldTab)
		if (F->Available == true) // Jeśli którekolwiek (przynajmniej jedno) pole jest dostępne
			return true;
	return false; // Jeśli sprawdziliśmy warunek dla całej tablicy
}
State EndOfGame(std::vector<Field*> &FieldTab, numberOfPawns nOP)
{
	// p1 - czarny, p2 - biały
	if (nOP.blacks == 0)
		return p2;
	if (nOP.whites == 0)
		return p1;
	
	for (Field* F : FieldTab) // Jeśli przynajmniej 1 pole jest puste
		if (F->Get() == none)
			return none;
	if (nOP.blacks > nOP.whites)
		return p1;
	else
		return p2;
}

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
	sf::RenderWindow window;// domyślne (780, 510)
	window.create(sf::VideoMode(840, 520), "Othello", sf::Style::Close);	
	Board board({ 0.0f, 0.0f });
	Field field[8][8];
	float fieldSize, pawnSize;
	SideMenu sideMenu;

	setup_DrawFields(board, field, fieldSize); // Procedura rysująca nam wszystkie pola
	std::vector <Field*> FieldTab; // Wektor wskaźników na pole

	setup_FillFieldTab(FieldTab, field); // Wstawiamy do wektora adresy wszystkich 64 pól w tablicy
	pawnSize = 0.8f * fieldSize;
	field[0][0].setPawnShadow(pawnSize);
	field[0][0].updatePawnShadow(p1);
	setup_DrawSideMenu(sideMenu, window, board); // Procedura rysująca menu boczne
	std::vector <Pawn*> PawnTab;  // Wektor przechowujący adresy wszystkich pionków (które znajdują się obecnie na planszy)
	setup_FirstPawns(PawnTab, field, pawnSize); // Procedura tworząca 4 startowe pionki
	
	State curPlayer = p1; // Zmienna przechowująca indeks bieżącego gracza (wykonującego ruch)
	numberOfPawns numberOfPawns; // Struktura zawierająca info o bieżącej liczbie białych i czarnych(potrzebna do menu bocznego)
	setup_Versor();
	UpdateAvailableFields(FieldTab, field, curPlayer); // Początkowy update pól
	bool mouseReleased = true; // Zabezpieczenie: stawianie pionków nie powinno być możliwe przy stale wciśniętym klawiszy myszy
	sf::Event event;
	sf::Vector2f cursorPosition;
	Field *fCur = &field[1][3];
	
	while (window.isOpen())//=================//
	{
		while (window.pollEvent(event))	
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				mouseReleased = true;
				break;
			}
		
		window.clear(sf::Color(140, 112, 60));
		board.draw(window);
		sideMenu.update_clock_message1();
		sideMenu.draw(window); // Wszystkie komponenty menu bocznego są już rysowane w tej metodzie	
		for (Field *f : FieldTab)  f->draw(window);
		for (Pawn *p : PawnTab)  p->draw(window);

		cursorPosition = { static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y) };
		
		for (Field *f : FieldTab)	
			if (cursorEntered(*f, cursorPosition))
			{
				fCur = f;
				break;
			}
			
		if (fCur->Available)
		{
			fCur->setPawnShadowPosition();
			window.draw(fCur->pawnShadow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseReleased) // Jeśli klikniemy na najechane pole, to...
			{
				Pawn *P = new Pawn(*fCur, curPlayer, pawnSize); // Tworzymy na tym polu właściwy pionek
				PawnTab.push_back(P); // Pionek wstawiamy do wektora
				moveOn(field, fCur, curPlayer); // Zmiana odpowiednich pionków
				numberOfPawns.update(FieldTab);
				ChangePlayer(curPlayer); // Zmieniamy gracza bieżącego			
				
				UpdateAvailableFields(FieldTab, field, curPlayer); // Aktualizacja dostępnych pól
				if (!IsAnyMoveAvailable(FieldTab)) // Jeśli żadne pole nie jest dla zmienionego gracza dostępne
				{
					ChangePlayer(curPlayer); // to wracamy do poprzedniego gracza
					UpdateAvailableFields(FieldTab, field, curPlayer); // Ponowna aktualizacja
					std::cout << "Gracz " << opponentIndex(curPlayer) << " nie ma dostepnych ruchow. Kontynuuje " << curPlayer << std::endl;
					sideMenu.show_message1("NoMoveAvailable", curPlayer);
				}
				State EoG = EndOfGame(FieldTab, numberOfPawns);
				if (EoG != none)
					sideMenu.show_message1("EndOfGame", EoG);
				fCur->updatePawnShadow(curPlayer);
				sideMenu.update(curPlayer, numberOfPawns);
				mouseReleased = false; // Zabezpieczenie
			}
		}
		
		window.display();
	}//=======================================//
	FieldTab.clear();
	PawnTab.clear();

    return 0;
}

