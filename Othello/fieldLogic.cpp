#include "stdafx.h"
#include "fieldLogic.h"

std::vector <pair_> Versor;

void setup_Versor()
{
	Versor = std::vector<pair_>{ pair_(-1, -1), pair_(-1, 0), pair_(-1, 1), pair_(0, -1),
		pair_(0,1), pair_(1,-1), pair_(1,0), pair_(1,1) };
	// Nasza tablica zawiera wektory jednostkowe (wersory) stanowi¹ce przesuniêcie w 1 z mo¿liwych 8 kierunków na planszy
}

// Funkcja zwracaj¹ca adres pola przesuniêtego o dany wersor wzglêdem *F (lub nullptr jeœli
// takiego s¹siada nie ma, bo jesteœmy przy krawêdzi planszy)
Field *neighbr(Field tab[][8], Field *F, pair_ versor)
{
	int indX = F->X() + versor.first;
	int indY = F->Y() + versor.second;
	if (indX < 0 || indX > 7 || indY < 0 || indY > 7)
		return nullptr;
	else
		return &tab[indX][indY];
}

State opponentIndex(State playerIndex)
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
bool isMoveValid(Field tab[][8], Field *F, State plInd)
{
	State oppInd = opponentIndex(plInd); // Indeks przeciwnika
	for (pair_ versor : Versor) // Dla ka¿dego z 8 wersorów (8 kierunków)
	{
		Field *N = neighbr(tab, F, versor); // Znajdujemy adres s¹siada PRZESUNIÊTEGO O DANY WERSOR
		if (N == nullptr)
			continue;
		if (N->Get() == oppInd) // Jeœli ten s¹siad nale¿y do przeciwnika
		{
			while (true)
			{				 
				Field *Npp = neighbr(tab, N, versor); // Bierzemy nastêpnika pola N
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

void changePawns(Field tab[][8], Field *F, State plInd)
{
	State oppInd = opponentIndex(plInd);
	for (pair_ versor : Versor) // Dla ka¿dego z 8 wersorów (8 kierunków)
	{
		Field *N = neighbr(tab, F, versor); // Znajdujemy adres s¹siada PRZESUNIÊTEGO O DANY WERSOR
		if (N == nullptr)
			continue;
		if (N->Get() == oppInd) // Jeœli ten s¹siad nale¿y do przeciwnika
		{
			std::vector <Field*> ToChange; // Wektor adresów pól do zmiany
			ToChange.push_back(N); // Wstêpnie wstawiamy N
			while (true)
			{
				Field *Npp = neighbr(tab, N, versor); // Bierzemy nastêpnika pola N
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


// Poni¿sze funkcje jednak siê nie przyda³y

/*

std::pair <int, int> findIndex(Field tab[][8], Field *F) // Znajduje indeks obiektu(pola) w 2-wym. tablicy obiektów
{
	std::pair <int, int> result(-1, -1); // Zabezpieczenie: jeœli nie znajdzie siê w tablicy adres pola F, to wynik bêdzie (-1, -1), czyli ujemny
	for (int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if (&tab[i][j] == F) // Jeœli zachodzi równoœæ adresów tych pól
			{
				result.first = i;
				result.second = j;
			}
	return result;
}
Field *left(Field tab[][8], Field *F) // Dla podanego adresu pola zwraca wskaŸnik na pole znajduj¹ce siê na lewo w tablicy
{
	std::pair<int, int> ind = findIndex(tab, F); // Znajdujemy indeks pola pod adresem F w tablicy tab
	if (ind == std::pair<int, int>(-1, -1)) // Jeœli nie znalaz³ siê indeks
		return nullptr;
	if (ind.first - 1 < 0) // Jeœli pola znajduje siê "na krawêdzi" tablicy lub nie znaleziono indeksu
		return nullptr;
	else
		return &tab[ind.first - 1][ind.second];
}
Field *right(Field tab[][8], Field *F) // Zwraca wskaŸnik na pole znajduj¹ce siê na prawo w tablicy
{
	std::pair<int, int> ind = findIndex(tab, F); // Znajdujemy indeks pola pod adresem F w tablicy tab
	if (ind == std::pair<int, int>(-1, -1))
		return nullptr;
	if (ind.first + 1 > 7)
		return nullptr;
	else
		return &tab[ind.first + 1][ind.second];
}
Field *top(Field tab[][8], Field *F) // Zwraca wskaŸnik na pole znajduj¹ce siê na górê
{
	std::pair<int, int> ind = findIndex(tab, F); // Znajdujemy indeks pola pod adresem F w tablicy tab
	if (ind == std::pair<int, int>(-1, -1))
		return nullptr;
	if (ind.second - 1< 0)
		return nullptr;
	else
		return &tab[ind.first][ind.second - 1];
}
Field *bottom(Field tab[][8], Field *F) // Zwraca wskaŸnik na pole znajduj¹ce siê na dó³
{
	std::pair<int, int> ind = findIndex(tab, F); // Znajdujemy indeks pola pod adresem F w tablicy tab
	if (ind == std::pair<int, int>(-1, -1))
		return nullptr;
	if (ind.second + 1 > 7)
		return nullptr;
	else
		return &tab[ind.first][ind.second + 1];
}

*/