#pragma once
#include "GameObject.h"
#include "Renderer.hpp"
//#include "Field.h"

class Pawn;

typedef std::vector<std::shared_ptr<Pawn>> _pawnPointers;
typedef std::shared_ptr<Pawn> _pawnPtr;


class Field;

class Pawn : public GameObject
{

private:
	static const std::string file_name_b;
	static const std::string file_name_w;
	static sf::Texture *texture_b;
	static sf::Texture *texture_w;
	static float pawnSize;

	static void setTextures();
		
public:
	friend class Creator;
	Pawn(){}
	Pawn(Field &F, FieldState playerIndex);
	
	~Pawn();
	void Place(std::vector<Pawn*> &pawnTab);
	void Set(FieldState playerIndex);

	static float getPawnSize();

	static void Clear();
};

