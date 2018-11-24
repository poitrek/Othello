#include "stdafx.h"
#include "Renderer.hpp"


std::vector<std::vector<GameObject*> > Renderer::objects;
std::vector<std::vector<GameObject*> > Renderer::temp_objects;

int Renderer::number_of_layers{ 0 };
//int Renderer::layer_iterator{ 0 };


Renderer::Renderer(int numberOfLayers)
{
	for (int i = 0; i < numberOfLayers; i++)
	{
		objects.push_back(obj_vect());
	}
	number_of_layers = numberOfLayers;
}

void Renderer::AddLayers(int n)
{
	for (int i = 0; i < n; i++)
	{
		objects.push_back(obj_vect());
		temp_objects.push_back(obj_vect());
	}
	number_of_layers = n;
}

void Renderer::Add(GameObject * obj, int layerId)
{
	objects[layerId - 1].push_back(obj);
}

void Renderer::AddOnTop(GameObject * obj)
{
	objects[number_of_layers - 1].push_back(obj);
}

void Renderer::Draw(GameObject * obj, int layerId)
{
	temp_objects[layerId - 1].push_back(obj);
}

void Renderer::Remove(GameObject * obj)
{
	// To do: given pointer to the object has to be found first
	// and then removed from the proper layer
	// Erase-remove idiom
	//objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());


	for (std::vector<GameObject*> &layer : objects)
	{
		layer.erase(std::remove(layer.begin(), layer.end(), obj), layer.end());
	}

}

void Renderer::Remove(GameObject * obj, int layerId)
{
	std::vector<GameObject*> &layer = objects[layerId];

	layer.erase(std::remove(layer.begin(), layer.end(), obj), layer.end());	
}

void Renderer::DrawAll(sf::RenderTarget &target)
{
	// For EVERY layer
	for (int i = 0; i < number_of_layers; i++)
	{
		// For EVERY object in the layer

		// Drawing permanent objects that were added to the vector
		for (auto it = objects[i].begin(); it != objects[i].end(); it++)
		{
			if ((*it) != nullptr)
			{
				(*it)->draw(target);
			}
		}
		// Drawing temporary objects that were called to be drawn in a given game loop
		for (auto it = temp_objects[i].begin(); it != temp_objects[i].end(); it++)
		{
			if ((*it) != nullptr)
			{
				(*it)->draw(target);
			}
		}
	}

	// Removing temporary objects
	for (int i = 0; i < number_of_layers; i++)
	{
		temp_objects[i].clear();
	}

}

void Renderer::Clear()
{
	for (int i = 0; i < number_of_layers - 1; i++)
		objects[i].clear();
	objects.clear();
}
