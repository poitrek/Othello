#pragma once
#include "GameObject.h"
#include "Pawn.h"
#include "circleTexture.h"

class Field : public GameObject
{
private:
	static const std::string file_name; // Nazwa pliku przechowuj�cego tekstur� pola
	static sf::Texture *texture;
	static float fieldSize;
	float scaleFactor{ 0.25f }; /// Czynnik, przez jaki musimy przemno�y� wymiary tekstury, aby uzyska�
							    ///  ��dane wymiary sprite'a (chyba ju� niepotrzebne)

	FieldState state; // Stan pola (przynale�no��)
	Pawn *pawn; // Wska�nik na (ewentualny) znajduj�cy si� na polu pionek
	int ind_X;
	int ind_Y;

	static int _ref_count;
public:
	Field();  // Domy�lny konstruktor
	~Field();

	sf::Vector2f getSize();
	void SetState(FieldState _state); // Ustawiamy stan pola
	FieldState GetState() { return state; } // Sprawdzamy stan pola
	void setX(int X) { ind_X = X; }
	void setY(int Y) { ind_Y = Y; }
	int X() { return ind_X; }
	int Y() { return ind_Y; }
	bool Available; // Informacja o tym, czy w danym momencie gry na polu dany gracz mo�e postawi� pionek
	
	void setPosition(float x, float y); // Ustawiamy pozycj� z u�yciem 2 float'�w
	
	static GameObject* pawnShadow; // Pojawiaj�ca si� po�wiata pionka, gdy chcemy go postawi�
	
	
	static void setPawnShadow();
	static void updatePawnShadow(FieldState curPlayer);
	static void setPawnShadowPosition(Field *field);
	
	friend class Creator;
	friend Pawn::Pawn(Field&, FieldState); // Konstruktor klasy Pionek jest funkcj� zaprzyja�nion� z t� klas�
};

