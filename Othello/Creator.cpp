#include "stdafx.h"
#include "Creator.hpp"

void Creator::DrawFields(Board & board, Field **&fieldTab)
{
	//sf::Vector2f fieldSize = fieldTab[0][0].getSize();
	sf::Vector2f posBuf{ 12.0f, 12.0f };

	Field::fieldSize = (board.getSize().x - 2 * posBuf.x) / 8.0f; // Odpowiedni rozmiar pola dostosowany do rozmiarów planszy
	std::cout << board.getSize().x << ", " << board.getSize().y << std::endl;
	std::cout << Field::fieldSize << std::endl;

	// Alokujemy pamiêæ tabeli
	fieldTab = new Field*[8];
	for (int i = 0; i < 8; i++)
	{
		fieldTab[i] = new Field[8];
	}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			fieldTab[i][j].setX(i); fieldTab[i][j].setY(j);
			fieldTab[i][j].setSize({ Field::fieldSize, Field::fieldSize }); // Nastawiamy rozmiar pola na ten w³aœciwy
			fieldTab[i][j].setPosition(board.getPosition().x + posBuf.x + i * Field::fieldSize,
				board.getPosition().y + posBuf.y + j * Field::fieldSize); // i konsekwentn¹ pozycjê
		}
	std::cout << fieldTab[0][0].getSize().x << ", " << fieldTab[0][0].getSize().y << std::endl;
}

std::vector<Field*> Creator::SetFieldVector(Field **fieldTab)
{
	std::vector<Field*> FieldVector;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			FieldVector.push_back(&fieldTab[i][j]);
			Renderer::Add(&fieldTab[i][j], 2);
		}

	return FieldVector;
}

void Creator::FirstPawns(std::vector<Pawn*> &PawnVector, Field **field)
{
	Pawn *veryFirst = new Pawn;
	veryFirst->setTextures();
	//Pawn::setTextures();
	Pawn::pawnSize = 0.8f * Field::fieldSize;

	Pawn *pawn1 = new Pawn(field[3][3], p2);
	Pawn *pawn2 = new Pawn(field[3][4], p1);
	Pawn *pawn3 = new Pawn(field[4][3], p1);
	Pawn *pawn4 = new Pawn(field[4][4], p2);

	PawnVector.push_back(pawn1);
	PawnVector.push_back(pawn2);
	PawnVector.push_back(pawn3);
	PawnVector.push_back(pawn4);

	Renderer::Add(pawn1, 3);
	Renderer::Add(pawn2, 3);
	Renderer::Add(pawn3, 3);
	Renderer::Add(pawn4, 3);

	delete veryFirst;
}

void Creator::CreateSideMenu(SideMenu &sideMenu, sf::RenderWindow & window, Board & board)
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
