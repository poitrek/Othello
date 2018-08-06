#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

typedef std::vector<GameObject*> obj_vect;

class Renderer
{	
	static std::vector< obj_vect > objects;
	static std::vector< obj_vect > temp_objects;

	//static int layer_iterator;
	static int number_of_layers;
	
public:
	Renderer(int numberOfLayers);

	static void Add(GameObject *obj, int layerId);
	static void AddOnTop(GameObject *obj);
	static void Draw(GameObject *obj, int layerId);

	static void Remove(GameObject *obj);

	static void DrawAll(sf::RenderTarget &);
	static void Clear();

	static void AddLayers(int n);


};

