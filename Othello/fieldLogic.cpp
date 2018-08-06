#include "stdafx.h"
#include "fieldLogic.h"

std::vector <pair_> Versor;

void setup_Versor()
{
	Versor = std::vector<pair_>{ pair_(-1, -1), pair_(-1, 0), pair_(-1, 1), pair_(0, -1),
		pair_(0,1), pair_(1,-1), pair_(1,0), pair_(1,1) };
	// Nasza tablica zawiera wektory jednostkowe (wersory) stanowi�ce przesuni�cie w 1 z mo�liwych 8 kierunk�w na planszy
}

// Funkcja zwracaj�ca adres pola przesuni�tego o dany wersor wzgl�dem *F (lub nullptr je�li
// takiego s�siada nie ma, bo jeste�my przy kraw�dzi planszy)
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

// Funkcja sprawdzaj�ca, czy na polu o adresie F gracz o indeksie plInd mo�e postawi� pionek
bool isMoveValid(Field tab[][8], Field *F, State plInd)
{
	State oppInd = opponentIndex(plInd); // Indeks przeciwnika
	for (pair_ versor : Versor) // Dla ka�dego z 8 wersor�w (8 kierunk�w)
	{
		Field *N = neighbr(tab, F, versor); // Znajdujemy adres s�siada PRZESUNI�TEGO O DANY WERSOR
		if (N == nullptr)
			continue;
		if (N->Get() == oppInd) // Je�li ten s�siad nale�y do przeciwnika
		{
			while (true)
			{				 
				Field *Npp = neighbr(tab, N, versor); // Bierzemy nast�pnika pola N
				if (Npp == nullptr) // Je�li nast�pnik N nie istnieje (jeste�my przy kraw�dzi planszy)
					break;
				if (Npp->Get() == none) // Je�li nast�pnik N jest pusty, to ruch w tym kierunku niedozwolony
					break;
				if (Npp->Get() == oppInd) // Je�li nast�pnik N te� nale�y do przeciwnika, jedziemy dalej
				{
					N = Npp;
					continue;
				}
				if (Npp->Get() == plInd) // Je�li nast�pnik N nale�y do nas, to ruch w tym kierunku jest mo�liwy
					return true;
			}
		}
	}
	return false; // Je�li sprawdzili�my wszystkie kierunki (wszystkie wersory) bez dost�pnego ruchu, to ruch nie jest dost�pny
}

void changePawns(Field tab[][8], Field *F, State plInd)
{
	State oppInd = opponentIndex(plInd);
	for (pair_ versor : Versor) // Dla ka�dego z 8 wersor�w (8 kierunk�w)
	{
		Field *N = neighbr(tab, F, versor); // Znajdujemy adres s�siada PRZESUNI�TEGO O DANY WERSOR
		if (N == nullptr)
			continue;
		if (N->Get() == oppInd) // Je�li ten s�siad nale�y do przeciwnika
		{
			std::vector <Field*> ToChange; // Wektor adres�w p�l do zmiany
			ToChange.push_back(N); // Wst�pnie wstawiamy N
			while (true)
			{
				Field *Npp = neighbr(tab, N, versor); // Bierzemy nast�pnika pola N
				if (Npp == nullptr) // Je�li nast�pnik N nie istnieje (jeste�my przy kraw�dzi planszy)
					break;
				if (Npp->Get() == none) // Je�li nast�pnik N jest pusty, to ruch w tym kierunku niedozwolony
					break;
				if (Npp->Get() == oppInd) // Je�li nast�pnik N te� nale�y do przeciwnika, jedziemy dalej
				{
					ToChange.push_back(Npp);
					N = Npp;
					continue;
				}
				if (Npp->Get() == plInd) // Je�li nast�pnik N nale�y do nas, to ruch w tym kierunku jest mo�liwy
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


// Poni�sze funkcje jednak si� nie przyda�y

/*

std::pair <int, int> findIndex(Field tab[][8], Field *F) // Znajduje indeks obiektu(pola) w 2-wym. tablicy obiekt�w
{
	std::pair <int, int> result(-1, -1); // Zabezpieczenie: je�li nie znajdzie si� w tablicy adres pola F, to wynik b�dzie (-1, -1), czyli ujemny
	for (int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if (&tab[i][j] == F) // Je�li zachodzi r�wno�� adres�w tych p�l
			{
				result.first = i;
				result.second = j;
			}
	return result;
}
Field *left(Field tab[][8], Field *F) // Dla podanego adresu pola zwraca wska�nik na pole znajduj�ce si� na lewo w tablicy
{
	std::pair<int, int> ind = findIndex(tab, F); // Znajdujemy indeks pola pod adresem F w tablicy tab
	if (ind == std::pair<int, int>(-1, -1)) // Je�li nie znalaz� si� indeks
		return nullptr;
	if (ind.first - 1 < 0) // Je�li pola znajduje si� "na kraw�dzi" tablicy lub nie znaleziono indeksu
		return nullptr;
	else
		return &tab[ind.first - 1][ind.second];
}
Field *right(Field tab[][8], Field *F) // Zwraca wska�nik na pole znajduj�ce si� na prawo w tablicy
{
	std::pair<int, int> ind = findIndex(tab, F); // Znajdujemy indeks pola pod adresem F w tablicy tab
	if (ind == std::pair<int, int>(-1, -1))
		return nullptr;
	if (ind.first + 1 > 7)
		return nullptr;
	else
		return &tab[ind.first + 1][ind.second];
}
Field *top(Field tab[][8], Field *F) // Zwraca wska�nik na pole znajduj�ce si� na g�r�
{
	std::pair<int, int> ind = findIndex(tab, F); // Znajdujemy indeks pola pod adresem F w tablicy tab
	if (ind == std::pair<int, int>(-1, -1))
		return nullptr;
	if (ind.second - 1< 0)
		return nullptr;
	else
		return &tab[ind.first][ind.second - 1];
}
Field *bottom(Field tab[][8], Field *F) // Zwraca wska�nik na pole znajduj�ce si� na d�
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