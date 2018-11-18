#pragma once
#include <SFML\Graphics.hpp>
enum FieldState { p1, p2, none };
// Stan pola - czy nale¿y do gracza 1, gracza 2, czy jest puste



class GameObject// : public sf::Drawable
{

protected:
	///std::string file_name;
	sf::Texture texture; // Tekstura obiektu graficznego

	//sf::Drawable * toDraw;

	sf::Sprite sprite;

public:

	GameObject();
	GameObject(sf::Texture *txtr);

	void setTexture(sf::Texture *txtr);

	void setSize(sf::Vector2f);	// NADAJEMY SPRITE'OWI WYMIARY przy u¿yciu skalowania wymiarów tekstury
	virtual sf::Vector2f getSize(); // ZWRACA WYMIARY SPRITE'A na podstawie wymiarów tekstury oraz skali
	void setPosition(sf::Vector2f);
	virtual sf::Vector2f getPosition();
	void setOriginToCenter();
	sf::Sprite *getSprite();

	virtual void draw(sf::RenderTarget& target);


	int GetObjectId();
	static int GetNumberOfObjects();

private:
	int object_id;
	void set_id();

	static int number_of_objects;

};
