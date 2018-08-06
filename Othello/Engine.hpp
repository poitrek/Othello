#pragma once
#include "Field.h"
#include "SideMenu.h"
#include "MouseHandler.hpp"

typedef std::pair<int, int> pair_;

class Engine
{

public:

	static Field **FieldTab;
		
	static void MakeTheMove(std::vector<Field*> &FieldVector, std::vector<Pawn*> &PawnVector);

	static void HandleNextMove(std::vector<Field*> &FieldVector, SideMenu &sideMenu);

	static void HandleMouseHover(std::vector<Field*> &FieldVector, sf::RenderTarget &target);

	static void HandlePlayerMove(std::vector<Field*> &FieldVector, std::vector<Pawn*> &PawnVector, SideMenu &sideMenu, sf::RenderTarget &target);


	static void UpdateAvailableFields(std::vector<Field*> &FieldVector);

	static bool IsAnyMoveAvailable();

	static void ChangeCurrentPlayer();

	static State EndOfGame(std::vector<Field*> &FieldVector);

	

	struct NumberOfPawns {
		static int blacks;
		static int whites;
		static void update(std::vector <Field*> &FieldTab)
		{
			int b = 0, w = 0;
			for (Field *F : FieldTab)
			{
				if (F->Get() == p1)
					b++;
				if (F->Get() == p2)
					w++;
			}
			blacks = b;
			whites = w;
			//std::cout << "Number of pawns: black " << blacks << ", white " << whites << std::endl;
		}
	};
	
	static State GetCurrentPlayer();
	


	static void Clear();

private:

	static Field * fCur;

	static State CurPlayer;

	static std::vector<Field*> AvailableFields;




	struct Logic	{
		
		static std::vector <pair_> Versor;

		static void setup_Versor();

		// Funkcja zwracaj¹ca indeks przeciwnika danego gracza
		static State opponentIndex(State playerIndex);

		// Funkcja zwracaj¹ca adres pola przesuniêtego o dany wersor wzglêdem *F (lub nullptr jeœli
		// takiego s¹siada nie ma, bo jesteœmy przy krawêdzi planszy)
		static Field *neighbr(Field *F, pair_ versor);

		// Funkcja sprawdzaj¹ca, czy na polu o adresie F gracz o indeksie plInd mo¿e postawiæ pionek
		static bool isMoveValid(Field *F, State plInd);

		// Funkcja zmieniaj¹ca odpowiednie pionki po wykonaniu ruchu
		static void changePawns(Field *F, State plInd);


	};
	
};

