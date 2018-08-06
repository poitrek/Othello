#pragma once
#include "GameObject.h"
#include "Renderer.hpp"
//#include "Field.h"
class Field;

class Pawn : public GameObject
{

private:
	static const std::string file_name_b;
	static const std::string file_name_w;
	static sf::Texture *texture_b;
	static sf::Texture *texture_w;
	static float pawnSize;

	void setTextures();
		
public:
	friend class Creator;
	Pawn(){}
	Pawn(Field &F, State playerIndex);
	
	~Pawn();
	void Place(std::vector<Pawn*> pawnTab);
	void Set(State playerIndex);

	static float getPawnSize();

};

