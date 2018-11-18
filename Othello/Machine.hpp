#pragma once
#include "Engine.hpp"
#include <SFML/System.hpp>

class Machine
{
public:
	
	//Field * ChosenField;

	static bool isReady();

	static Field * ChooseField();


	Machine();
	~Machine();

private:
	static bool isWaiting;
	static sf::Clock waitTimer;
	static const float waitDuration;

};

