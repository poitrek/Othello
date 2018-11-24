#pragma once
#include "GameObject.h"
#include "Field.h"
#include <vector>
#include <memory>

class BoardFeatures
{
public:
	static std::vector<std::shared_ptr<GameObject>> AvailableFieldsFrames;
	static std::shared_ptr<GameObject> pawnShadow;

	static void Init();

	// Sets PawnShadow position and color according to given field and player index
	static void SetPawnShadow(Field *field, FieldState PlayerIndex);

	// Creates and places all of needed frames on passed available fields
	static void SetAvailableFieldsFrames(const std::vector<Field*> &AvailableFields);

	static void Clear();

private:
	static void initPawnShadow();
	static void initFrameTexture();

	static const std::string frameTexture_filename;
	//static std::shared_ptr<sf::Texture> frameTexture;
	static sf::Texture* frameTexture;

	static std::shared_ptr<GameObject> NewFieldFrame(Field *field);

};

