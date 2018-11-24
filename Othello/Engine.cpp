#include "stdafx.h"
#include "Engine.hpp"
#include "Game.hpp"
#include "BoardFeatures.hpp"

Field* Engine::fCur{ nullptr };

FieldState Engine::CurPlayer{ p1 };

const FieldState Engine::PlayerIndex{ p1 };
const FieldState Engine::ComputerIndex{ p2 };

std::vector<Field*> Engine::AvailableFields;


Field** Engine::FieldTab{ nullptr };


int Engine::NumberOfPawns::blacks{ 2 };
int Engine::NumberOfPawns::whites{ 2 };



void Engine::MakeTheMove(std::vector<Field*> &FieldVector, _pawnPointers &PawnVector, Field *field)
{
	_pawnPtr pp = _pawnPtr(new Pawn(*field, CurPlayer));

	PawnVector.push_back(pp);
	Renderer::Add(pp.get(), 3);

	/*
	Pawn *P = new Pawn(*field, CurPlayer); // Tworzymy na tym polu w³aœciwy pionek
	//P->Place(PawnVector);
	PawnVector.push_back(P); // Pionek wstawiamy do wektora
	Renderer::Add(P, 3);
	*/

	auto FieldsToAttack = Logic::findAttackedPawns(field, CurPlayer); // Zmieniamy odpowiednie pionki
	ResolveFields(FieldsToAttack, CurPlayer);
	
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
	FieldState IGO = Engine::IsGameOver(FieldVector);
	if (IGO != none)
	{
		Game::State = Game::Over;
		sideMenu.show_message1("EndOfGame", IGO);
	}
	fCur->updatePawnShadow(CurPlayer);

	std::pair<int, int> nOP_pair;
	nOP_pair.first = NumberOfPawns::blacks;
	nOP_pair.second = NumberOfPawns::whites;

	sideMenu.update(Engine::GetCurrentPlayer(), nOP_pair);

	
	// Remove recent field frames
	for (std::shared_ptr<GameObject> fieldFrame : BoardFeatures::AvailableFieldsFrames)
	{
		Renderer::Remove(fieldFrame.get());
	}

	// Update available field frames
	BoardFeatures::SetAvailableFieldsFrames(Engine::AvailableFields);

	// Add updated field frames to the Renderer again
	for (std::shared_ptr<GameObject> fieldFrame : BoardFeatures::AvailableFieldsFrames)
	{
		Renderer::Add(fieldFrame.get(), 3);
	}
	

}

void Engine::HandleMouseHover(std::vector<Field*>& FieldVector)
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
		if (MouseHandler::mouseHovered(f))
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
	_pawnPointers &PawnVector, SideMenu &sideMenu)
{

	if (fCur != nullptr)
		if (MouseHandler::mouseClicked(*fCur))
		{
			Engine::MakeTheMove(FieldVector, PawnVector, fCur);
			Engine::HandleNextMove(FieldVector, sideMenu);
		}

}

void Engine::ResolveFields(std::vector<Field*>& AttackedFields, FieldState NewOwner)
{
	for (Field *f : AttackedFields)
	{
		f->SetState(NewOwner);
	}
}

void Engine::UpdateAvailableFields(std::vector<Field*>& FieldVector)
{
	AvailableFields.clear();

	for (Field *F : FieldVector)
	{
		bool _add;

		if (F->GetState() != none)
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

FieldState Engine::IsGameOver(std::vector<Field*>& FieldVector)
{
	// p1 - czarny, p2 - bia³y
	if (NumberOfPawns::blacks == 0)
		return p2;
	if (NumberOfPawns::whites == 0)
		return p1;

	for (Field* F : FieldVector) // Jeœli przynajmniej 1 pole jest puste
		if (F->GetState() == none)
			return none;
	if (NumberOfPawns::blacks > NumberOfPawns::whites)
		return p1;
	else
		return p2;
}

FieldState Engine::GetPlayerIndex()
{
	return FieldState(PlayerIndex);
}

FieldState Engine::GetComputerIndex()
{
	return FieldState(ComputerIndex);
}

FieldState Engine::GetCurrentPlayer()
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

FieldState Engine::Logic::opponentIndex(FieldState playerIndex)
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
bool Engine::Logic::isMoveValid(Field *F, FieldState plInd)
{
	FieldState oppInd = opponentIndex(plInd); // Indeks przeciwnika
	for (pair_ versor : Versor) // Dla ka¿dego z 8 wersorów (8 kierunków)
	{
		Field *N = neighbr(F, versor); // Znajdujemy adres s¹siada PRZESUNIÊTEGO O DANY WERSOR
		if (N == nullptr)
			continue;
		if (N->GetState() == oppInd) // Jeœli ten s¹siad nale¿y do przeciwnika
		{
			while (true)
			{
				Field *Npp = neighbr(N, versor); // Bierzemy nastêpnika pola N
				if (Npp == nullptr) // Jeœli nastêpnik N nie istnieje (jesteœmy przy krawêdzi planszy)
					break;
				if (Npp->GetState() == none) // Jeœli nastêpnik N jest pusty, to ruch w tym kierunku niedozwolony
					break;
				if (Npp->GetState() == oppInd) // Jeœli nastêpnik N te¿ nale¿y do przeciwnika, jedziemy dalej
				{
					N = Npp;
					continue;
				}
				if (Npp->GetState() == plInd) // Jeœli nastêpnik N nale¿y do nas, to ruch w tym kierunku jest mo¿liwy
					return true;
			}
		}
	}
	return false; // Jeœli sprawdziliœmy wszystkie kierunki (wszystkie wersory) bez dostêpnego ruchu, to ruch nie jest dostêpny
}

std::vector<Field*> Engine::Logic::findAttackedPawns(Field *F, FieldState plInd)
{
	FieldState oppInd = opponentIndex(plInd);

	std::vector<Field*> FieldsToAttack;

	for (pair_ versor : Versor) // Dla ka¿dego z 8 wersorów (8 kierunków)
	{
		Field *N = neighbr(F, versor); // Znajdujemy adres s¹siada PRZESUNIÊTEGO O DANY WERSOR
		if (N == nullptr)
			continue;
		if (N->GetState() == oppInd) // Jeœli ten s¹siad nale¿y do przeciwnika
		{
			std::vector <Field*> ToChange; // Wektor adresów pól do zmiany
			ToChange.push_back(N); // Wstêpnie wstawiamy N
			while (true)
			{
				Field *Npp = neighbr(N, versor); // Bierzemy nastêpnika pola N
				if (Npp == nullptr) // Jeœli nastêpnik N nie istnieje (jesteœmy przy krawêdzi planszy)
					break;
				if (Npp->GetState() == none) // Jeœli nastêpnik N jest pusty, to ruch w tym kierunku niedozwolony
					break;
				if (Npp->GetState() == oppInd) // Jeœli nastêpnik N te¿ nale¿y do przeciwnika, jedziemy dalej
				{
					ToChange.push_back(Npp);
					N = Npp;
					continue;
				}
				if (Npp->GetState() == plInd) // Jeœli nastêpnik N nale¿y do nas, to ruch w tym kierunku jest mo¿liwy
				{
					/*for (Field *f : ToChange)
					{
						f->SetState(plInd);
					}
					break;
					*/
					FieldsToAttack.insert(FieldsToAttack.end(), ToChange.begin(), ToChange.end());
					
					break;
				}
			}
			ToChange.clear();
		}
	}

	return FieldsToAttack;

}
