#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

typedef std::vector<GameObject*> obj_vect;

class Renderer
{	

public:
	Renderer(int numberOfLayers);

	// Adds given object on the chosen layer to draw in every game loop
	static void Add(GameObject *obj, int layerId);

	// Adds given object on the top layer
	static void AddOnTop(GameObject *obj);

	// Adds object to a temporary collection to be drawn only in the current game loop
	static void Draw(GameObject *obj, int layerId);

	// Removes object from the constant drawing collection
	static void Remove(GameObject *obj);

	// Removes object only from given layer
	static void Remove(GameObject *obj, int layerId);

	static void DrawAll(sf::RenderTarget &);
	static void Clear();

	static void AddLayers(int n);

private:
	static std::vector< obj_vect > objects;
	static std::vector< obj_vect > temp_objects;

	// Draws an object if it's not a nullptr
	//static void drawObject(GameObject *obj, sf::RenderTarget &);

	//static int layer_iterator;
	static int number_of_layers;
	
};

