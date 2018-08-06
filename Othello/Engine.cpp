#include "stdafx.h"
#include "Engine.hpp"


Field* Engine::fCur{ nullptr };

State Engine::CurPlayer{ p1 };

std::vector<Field*> Engine::AvailableFields;


Field** Engine::FieldTab{ nullptr };


int Engine::NumberOfPawns::blacks{ 2 };
int Engine::NumberOfPawns::whites{ 2 };



void Engine::MakeTheMove(std::vector<Field*> &FieldVector, std::vector<Pawn*>& PawnVector)
{
	Pawn *P = new Pawn(*fCur, CurPlayer); // Tworzymy na tym polu w³aœciwy pionek
	//P->Place(PawnVector);
	PawnVector.push_back(P); // Pionek wstawiamy do wektora
	Renderer::Add(P, 3);

	Logic::changePawns(fCur, CurPlayer); // Zmieniamy odpowiednie pionki
	NumberOfPawns::update(FieldVector); // Update'ujemy liczby pionków

	ChangeCurrentPlayer(); // Zmieniamy gracza bie¿¹cego

	UpdateAvailableFields(FieldVector); // Aktualizacja dostêpnych pól

}

void Engine::HandleNextMove(std::vector<Field*>& FieldVector, SideMenu & sideMenu)
{
	if (!Engine::IsAnyMoveAvailable()) // Jeœli ¿adne pole nie jest dla zmienionego gracza dostêpne
	{
		Engine::ChangeCurrentPlayer(); // to wracamy do poprzedniego gracza
		Engine::UpdateAvailableFields(FieldVector); // Ponowna aktualizacja
		std::cout << "Gracz " << Logic::opponentIndex(CurPlayer) << " nie ma dostepnych ruchow. Kontynuuje " << CurPlayer << std::endl;
		sideMenu.show_message1("NoMoveAvailable", CurPlayer);
	}
	State EoG = Engine::EndOfGame(FieldVector);
	if (EoG != none)
		sideMenu.show_message1("EndOfGame", EoG);
	fCur->updatePawnShadow(CurPlayer);

	std::pair<int, int> nOP_pair;
	nOP_pair.first = NumberOfPawns::blacks;
	nOP_pair.second = NumberOfPawns::whites;

	sideMenu.update(Engine::GetCurrentPlayer(), nOP_pair);

}

void Engine::HandleMouseHover(std::vector<Field*>& FieldVector, sf::RenderTarget &target)
{
	/*
	fCur = nullptr;
	for (Field *f : FieldVector)
	{
		if (MouseHandler::mouseHovered(f, target))
		{
			fCur = f;
			break;
		}
	}
	*/

	fCur = nullptr;
	for (Field *f : Engine::AvailableFields)
	{
		if (MouseHandler::mouseHovered(f, target))
		{
			fCur = f;
			break;
		}
	}

	if (fCur)
	{
		Field::setPawnShadowPosition(fCur);

		Renderer::Draw(Field::pawnShadow, 3);
	}
	



}

void Engine::HandlePlayerMove(std::vector<Field*>& FieldVector,
	std::vector<Pawn*> &PawnVector, SideMenu &sideMenu, sf::RenderTarget & target)
{

	if (fCur != nullptr)
		if (MouseHandler::mouseClicked(*fCur, target))
		{
			Engine::MakeTheMove(FieldVector, PawnVector);
			Engine::HandleNextMove(FieldVector, sideMenu);
		}

}

void Engine::UpdateAvailableFields(std::vector<Field*>& FieldVector)
{
	AvailableFields.clear();

	for (Field *F : FieldVector)
	{
		bool _add;

		if (F->Get() != none)
			_add = false;
		else
		{
			_add = Logic::isMoveValid(F, CurPlayer);
		}
		if (_add)
			AvailableFields.push_back(F);
	}

}

bool Engine::IsAnyMoveAvailable()
{
	return !AvailableFields.empty();
}

void Engine::ChangeCurrentPlayer()
{
	if (CurPlayer == p1)
	{
		CurPlayer = p2;
		return;
	}
	if (CurPlayer == p2)
	{
		CurPlayer = p1;
		return;
	}
}

State Engine::EndOfGame(std::vector<Field*>& FieldVector)
{
	// p1 - czarny, p2 - bia³y
	if (NumberOfPawns::blacks == 0)
		return p2;
	if (NumberOfPawns::whites == 0)
		return p1;

	for (Field* F : FieldVector) // Jeœli przynajmniej 1 pole jest puste
		if (F->Get() == none)
			return none;
	if (NumberOfPawns::blacks > NumberOfPawns::whites)
		return p1;
	else
		return p2;
}

State Engine::GetCurrentPlayer()
{
	return CurPlayer;
}

void Engine::Clear()
{
	for (int i = 0; i < 8; i++)
		delete[] FieldTab[i];

	delete[] FieldTab;
}





std::vector<pair_> Engine::Logic::Versor{ pair_(-1, -1), pair_(-1, 0), pair_(-1, 1), pair_(0, -1),
pair_(0,1), pair_(1,-1), pair_(1,0), pair_(1,1) };


void Engine::Logic::setup_Versor()
{
	Versor = std::vector<pair_>{ pair_(-1, -1), pair_(-1, 0), pair_(-1, 1), pair_(0, -1),
		pair_(0,1), pair_(1,-1), pair_(1,0), pair_(1,1) };
	// Nasza tablica zawiera wektory jednostkowe (wersory) stanowi¹ce przesuniêcie w 1 z mo¿liwych 8 kierunków na planszy
}

// Funkcja zwracaj¹ca adres pola przesuniêtego o dany wersor wzglêdem *F (lub nullptr jeœli
// takiego s¹siada nie ma, bo jesteœmy przy krawêdzi planszy)
Field* Engine::Logic::neighbr(Field *F, pair_ versor)
{
	int indX = F->X() + versor.first;
	int indY = F->Y() + versor.second;
	if (indX < 0 || indX > 7 || indY < 0 || indY > 7)
		return nullptr;
	else
		return &FieldTab[indX][indY];
}

State Engine::Logic::opponentIndex(State playerIndex)
{
	switch (playerIndex)
	{
	case p1: return p2;
	case p2: return p1;
	case none: return none;
	default: return none;
	}
}

// Funkcja sprawdzaj¹ca, czy na polu o adresie F gracz o indeksie plInd mo¿e postawiæ pionek
bool Engine::Logic::isMoveValid(Field *F, State plInd)
{
	State oppInd = opponentIndex(plInd); // Indeks przeciwnika
	for (pair_ versor : Versor) // Dla ka¿dego z 8 wersorów (8 kierunków)
	{
		Field *N = neighbr(F, versor); // Znajdujemy adres s¹siada PRZESUNIÊTEGO O DANY WERSOR
		if (N == nullptr)
			continue;
		if (N->Get() == oppInd) // Jeœli ten s¹siad nale¿y do przeciwnika
		{
			while (true)
			{
				Field *Npp = neighbr(N, versor); // Bierzemy nastêpnika pola N
				if (Npp == nullptr) // Jeœli nastêpnik N nie istnieje (jesteœmy przy krawêdzi planszy)
					break;
				if (Npp->Get() == none) // Jeœli nastêpnik N jest pusty, to ruch w tym kierunku niedozwolony
					break;
				if (Npp->Get() == oppInd) // Jeœli nastêpnik N te¿ nale¿y do przeciwnika, jedziemy dalej
				{
					N = Npp;
					continue;
				}
				if (Npp->Get() == plInd) // Jeœli nastêpnik N nale¿y do nas, to ruch w tym kierunku jest mo¿liwy
					return true;
			}
		}
	}
	return false; // Jeœli sprawdziliœmy wszystkie kierunki (wszystkie wersory) bez dostêpnego ruchu, to ruch nie jest dostêpny
}

void Engine::Logic::changePawns(Field *F, State plInd)
{
	State oppInd = opponentIndex(plInd);
	for (pair_ versor : Versor) // Dla ka¿dego z 8 wersorów (8 kierunków)
	{
		Field *N = neighbr(F, versor); // Znajdujemy adres s¹siada PRZESUNIÊTEGO O DANY WERSOR
		if (N == nullptr)
			continue;
		if (N->Get() == oppInd) // Jeœli ten s¹siad nale¿y do przeciwnika
		{
			std::vector <Field*> ToChange; // Wektor adresów pól do zmiany
			ToChange.push_back(N); // Wstêpnie wstawiamy N
			while (true)
			{
				Field *Npp = neighbr(N, versor); // Bierzemy nastêpnika pola N
				if (Npp == nullptr) // Jeœli nastêpnik N nie istnieje (jesteœmy przy krawêdzi planszy)
					break;
				if (Npp->Get() == none) // Jeœli nastêpnik N jest pusty, to ruch w tym kierunku niedozwolony
					break;
				if (Npp->Get() == oppInd) // Jeœli nastêpnik N te¿ nale¿y do przeciwnika, jedziemy dalej
				{
					ToChange.push_back(Npp);
					N = Npp;
					continue;
				}
				if (Npp->Get() == plInd) // Jeœli nastêpnik N nale¿y do nas, to ruch w tym kierunku jest mo¿liwy
				{
					for (Field *f : ToChange)
					{
						f->Set(plInd);
					}
					break;
				}
			}
			ToChange.clear();
		}
	}
}
