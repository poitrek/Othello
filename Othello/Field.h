#pragma once
#include "ObiektGraficzny.h"
#include "Pawn.h"
#include "circleTexture.h"


class Field : public ObiektGraficzny
{
private:
	static const std::string file_name; // Nazwa pliku przechowuj�cego tekstur� pola
	static sf::Texture *texture;
	float scaleFactor{ 0.25f }; /// Czynnik, przez jaki musimy przemno�y� wymiary tekstury, aby uzyska�
							    ///  ��dane wymiary sprite'a (chyba ju� niepotrzebne)
	State state; // Stan pola (przynale�no��)
	Pawn *pawn; // Wska�nik na (ewentualny) znajduj�cy si� na polu pionek
	int ind_X;
	int ind_Y;
public:
	Field();  // Domy�lny konstruktor
	Field(sf::Vector2f position); // Konstruktor ustawiaj�cy pozycj� (niepotrzebny)
	~Field();

	sf::Vector2f getSize();
	void Set(State _state); // Ustawiamy stan pola
	State Get() { return state; } // Sprawdzamy stan pola
	void setX(int X) { ind_X = X; }
	void setY(int Y) { ind_Y = Y; }
	int X() { return ind_X; }
	int Y() { return ind_Y; }
	bool Available; // Informacja o tym, czy w danym momencie gry na polu dany gracz mo�e postawi� pionek
							
	void setPosition(float x, float y); // Ustawiamy pozycj� z u�yciem 2 float'�w
	
	static sf::Sprite pawnShadow; // Pojawiaj�ca si� po�wiata pionka, gdy chcemy go postawi�
	static void setPawnShadow(float pawnSize);
	static void updatePawnShadow(State curPlayer);
	void setPawnShadowPosition();
	void Highlight(State curPlayer, float pawnSize); /// Prawdopodobnie nie b�dzie potrzebne
	void Standard(); /// Prawdopodobnie nie b�dzie potrzebne

	//friend class Pawn;
	friend Pawn::Pawn(Field&, State, float); // Konstruktor klasy Pionek jest funkcj� zaprzyja�nion� z t� klas�
};

