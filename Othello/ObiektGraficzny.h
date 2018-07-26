#pragma once
#include <SFML\Graphics.hpp>
enum State { p1, p2, none };
// Stan pola - czy nale¿y do gracza 1, gracza 2, czy jest puste

class ObiektGraficzny// : public sf::Drawable
{
protected:
	///std::string file_name;
	sf::Texture texture; // Tekstura obiektu graficznego
	sf::Sprite sprite;

public:
	ObiektGraficzny();
	~ObiektGraficzny();

	void setSize(sf::Vector2f);	// NADAJEMY SPRITE'OWI WYMIARY przy u¿yciu skalowania wymiarów tekstury
	sf::Vector2f getSize(); // ZWRACA WYMIARY SPRITE'A na podstawie wymiarów tekstury oraz skali
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();

	virtual void draw(sf::RenderWindow& window);
	//void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};
