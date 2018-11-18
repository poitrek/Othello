#include "stdafx.h"
#include "Machine.hpp"
#include <SFML/System.hpp>

sf::Clock Machine::waitTimer;
bool Machine::isWaiting{ false };
const float Machine::waitDuration{ 2.0 };

bool Machine::isReady()
{
	if (!isWaiting)
	{
		isWaiting = true;
		waitTimer.restart();
		return false;
	}
	else
	{

		if (waitTimer.getElapsedTime().asSeconds() >= waitDuration)
		{
			isWaiting = false;
			return true;
		}
		else
		{
			return false;
		}
	}
}

Field * Machine::ChooseField()
{
	size_t maximumNumber = 0;
	Field * Candidate = nullptr;

	for (Field *F : Engine::AvailableFields)
	{
		// Finding the number of fields to attack from iterated field
		size_t numberOfFields = Engine::Logic::findAttackedPawns(F, Engine::ComputerIndex).size();
		if (numberOfFields > maximumNumber)
		{
			maximumNumber = numberOfFields;
			Candidate = F;
		}
	}

	return Candidate;
}

Machine::Machine()
{
}


Machine::~Machine()
{
}
