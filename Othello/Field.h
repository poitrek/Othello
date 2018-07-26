#pragma once
#include "ObiektGraficzny.h"
#include "Pawn.h"
#include "circleTexture.h"


class Field : public ObiektGraficzny
{
private:
	static const std::string file_name; // Nazwa pliku przechowuj¹cego teksturê pola
	static sf::Texture *texture;
	float scaleFactor{ 0.25f }; /// Czynnik, przez jaki musimy przemno¿yæ wymiary tekstury, aby uzyskaæ
							    ///  ¿¹dane wymiary sprite'a (chyba ju¿ niepotrzebne)
	State state; // Stan pola (przynale¿noœæ)
	Pawn *pawn; // WskaŸnik na (ewentualny) znajduj¹cy siê na polu pionek
	int ind_X;
	int ind_Y;
public:
	Field();  // Domyœlny konstruktor
	Field(sf::Vector2f position); // Konstruktor ustawiaj¹cy pozycjê (niepotrzebny)
	~Field();

	sf::Vector2f getSize();
	void Set(State _state); // Ustawiamy stan pola
	State Get() { return state; } // Sprawdzamy stan pola
	void setX(int X) { ind_X = X; }
	void setY(int Y) { ind_Y = Y; }
	int X() { return ind_X; }
	int Y() { return ind_Y; }
	bool Available; // Informacja o tym, czy w danym momencie gry na polu dany gracz mo¿e postawiæ pionek
							
	void setPosition(float x, float y); // Ustawiamy pozycjê z u¿yciem 2 float'ów
	
	static sf::Sprite pawnShadow; // Pojawiaj¹ca siê poœwiata pionka, gdy chcemy go postawiæ
	static void setPawnShadow(float pawnSize);
	static void updatePawnShadow(State curPlayer);
	void setPawnShadowPosition();
	void Highlight(State curPlayer, float pawnSize); /// Prawdopodobnie nie bêdzie potrzebne
	void Standard(); /// Prawdopodobnie nie bêdzie potrzebne

	//friend class Pawn;
	friend Pawn::Pawn(Field&, State, float); // Konstruktor klasy Pionek jest funkcj¹ zaprzyjaŸnion¹ z t¹ klas¹
};

