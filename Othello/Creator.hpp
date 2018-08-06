#pragma once
#include "Board.h"
#include "Field.h"
#include "SideMenu.h"
#include "Renderer.hpp"
class Creator
{
public:
	static void DrawFields(Board &board, Field **&fieldTab);
	static std::vector<Field*> SetFieldVector(Field **fieldTab);
	static void FirstPawns(std::vector<Pawn*> &PawnVector, Field **field);
	static void CreateSideMenu(SideMenu &sideMenu, sf::RenderWindow& window, Board& board);

};

