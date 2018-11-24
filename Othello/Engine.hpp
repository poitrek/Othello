#pragma once
#include "Field.h"
#include "SideMenu.h"
#include "MouseHandler.hpp"

class Machine;

typedef std::pair<int, int> pair_;

class Engine
{

public:

	friend class Machine;

	static Field **FieldTab;
	
	static void MakeTheMove(std::vector<Field*> &FieldVector, _pawnPointers &PawnVector, Field *field);

	static void HandleNextMove(std::vector<Field*> &FieldVector, SideMenu &sideMenu);

	static void HandleMouseHover(std::vector<Field*> &FieldVector);

	static void HandlePlayerMove(std::vector<Field*> &FieldVector, _pawnPointers &PawnVector, SideMenu &sideMenu);


	static void ResolveFields(std::vector<Field*> &AttackedFields, FieldState NewOwner);

	static void UpdateAvailableFields(std::vector<Field*> &FieldVector);

	static bool IsAnyMoveAvailable();

	static void ChangeCurrentPlayer();

	static FieldState IsGameOver(std::vector<Field*> &FieldVector);

	

	struct NumberOfPawns {
		static int blacks;
		static int whites;
		static void update(std::vector <Field*> &FieldTab)
		{
			int b = 0, w = 0;
			for (Field *F : FieldTab)
			{
				if (F->GetState() == p1)
					b++;
				if (F->GetState() == p2)
					w++;
			}
			blacks = b;
			whites = w;
			//std::cout << "Number of pawns: black " << blacks << ", white " << whites << std::endl;
		}
	};
	
	static FieldState GetPlayerIndex();

	static FieldState GetComputerIndex();

	static FieldState GetCurrentPlayer();
	


	static void Clear();

private:


	static FieldState CurPlayer;

	static const FieldState PlayerIndex;

	static const FieldState ComputerIndex;


	static Field * fCur;

	static std::vector<Field*> AvailableFields;




	struct Logic	{

		static std::vector <pair_> Versor;

		static void setup_Versor();

		// Funkcja zwracaj�ca indeks przeciwnika danego gracza
		static FieldState opponentIndex(FieldState playerIndex);

		// Funkcja zwracaj�ca adres pola przesuni�tego o dany wersor wzgl�dem *F (lub nullptr je�li
		// takiego s�siada nie ma, bo jeste�my przy kraw�dzi planszy)
		static Field *neighbr(Field *F, pair_ versor);

		// Funkcja sprawdzaj�ca, czy na polu o adresie F gracz o indeksie plInd mo�e postawi� pionek
		static bool isMoveValid(Field *F, FieldState plInd);

		// Funkcja zwracaj�ca wektor p�l/pionk�w atakowanych z pola F przez gracza plInd
		static std::vector<Field*> findAttackedPawns(Field *F, FieldState plInd);


	};
	
};

