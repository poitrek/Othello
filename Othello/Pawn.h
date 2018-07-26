#pragma once
#include "ObiektGraficzny.h"
//#include "Field.h"
class Field;

class Pawn : public ObiektGraficzny
{
private:
	static const std::string file_name_b;
	static const std::string file_name_w;
	static sf::Texture *texture_b;
	static sf::Texture *texture_w;
	
public:

	Pawn(Field &F, State playerIndex, float pawnSize);
	Pawn();
	~Pawn();
	void Set(State playerIndex);
	void setTextures();
};

