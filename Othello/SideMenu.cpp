#include "stdafx.h"
#include "SideMenu.h"
#include <iostream>


extern sf::Texture *texture_w;
extern sf::Texture *texture_b;
extern void tex_setup();

SideMenu::SideMenu()
{
	if (!texture.loadFromFile(file_name))
	{
		std::cout << "Error [SideMenu::SideMenu()]: nie udalo sie otworzyc pliku " << file_name << std::endl;
	}
	sprite.setTexture(texture);

}


SideMenu::~SideMenu()
{
}

void SideMenu::setLabels()
{
	if (!textfont.loadFromFile(font_file_name))
		std::cout << "Error [setup_Text]: nie udalo sie otworzyc pliku " << font_file_name << std::endl;
	label1.setFont(textfont);
	label2.setFont(textfont);
	label1.setString("Runda gracza:");
	label1.setCharacterSize(20);
	label2.setString("Liczba pionkow:");
	label2.setCharacterSize(20);
	sf::Vector2f pos1 = getPosition() + sf::Vector2f{20.0f, 30.0f};
	label1.setPosition(pos1);
	label2.setPosition(pos1 + sf::Vector2f{ 0, 160.0f });
		
	//tex_setup();
	playerThumbnail.setTexture(*texture_b);
	sf::Vector2f vec{55.0f, 55.0f};
	sf::Vector2f vec2{ 37.5f, 37.5f };
	setSpriteSize(playerThumbnail, vec);	
	playerThumbnail.setPosition(label1.getPosition() + sf::Vector2f(35.0f, 35.0f));

	playerThumbnail_b.setTexture(*texture_b);
	playerThumbnail_w.setTexture(*texture_w);
	setSpriteSize(playerThumbnail_b, vec2);
	setSpriteSize(playerThumbnail_w, vec2);
	playerThumbnail_w.setPosition(label2.getPosition() + sf::Vector2f(25.0f, 40.0f));
	playerThumbnail_b.setPosition(label2.getPosition() + sf::Vector2f(105.0f, 40.0f));

	num_b.setFont(textfont);
	num_w.setFont(textfont);
	num_b.setCharacterSize(24);
	num_w.setCharacterSize(24);
	num_b.setFillColor(sf::Color(180, 180, 180));
	num_w.setFillColor(sf::Color(180, 180, 180));
	num_w.setPosition(playerThumbnail_w.getPosition() + sf::Vector2f(15.0f, 40.0f));
	num_b.setPosition(playerThumbnail_b.getPosition() + sf::Vector2f(15.0f, 40.0f));
	num_w.setString(std::to_string(2));
	num_b.setString(std::to_string(2));

	message1.setFont(textfont);
	message1.setCharacterSize(15);
	message1.setString("Gracz nie ma dostepnych ruchow.");
	message1.setFillColor(sf::Color(255, 255, 125, 255));
	message1.setPosition(getPosition() + sf::Vector2f(14.0f, 340.0f));
	message1_enable = false;
}

void SideMenu::update(State curPlayer, numberOfPawns numberOfPawns)
{
	switch(curPlayer)
	{
	case p1:
		playerThumbnail.setTexture(*texture_b);
		break;
	case p2:
		playerThumbnail.setTexture(*texture_w);
	}
	num_b.setString(std::to_string(numberOfPawns.blacks));
	num_w.setString(std::to_string(numberOfPawns.whites));
}

void SideMenu::show_message1(std::string mode, State state = none)
{
	if (mode == "EndOfGame")
	{
		switch (state)
		{
		case p1:
			message1.setString("Koniec gry. Wygrywa Czarny!");
			break;
		case p2:
			message1.setString("Koniec gry. Wygrywa Bialy!");
			break;
		case none:
			message1.setString("Koniec gry. Remis!");
			break;
		}
		clock_message1_enable=false;
	}
	if (mode == "NoMoveAvailable")
	{
		if (state == p1)
			message1.setString("Bialy nie ma dostepnych ruchow.");
		if (state == p2)
			message1.setString("Czarny nie ma dostepnych ruchow.");
		clock_message1_enable=true;
	}
	message1_enable = true;
	clock_message1.restart();
}

void SideMenu::update_clock_message1()
{
	if (!clock_message1_enable)
		return;
	if (message1_enable)
	{
		sf::Time time = clock_message1.getElapsedTime();
		if (time.asSeconds() >= 5.0f)
			hide_message1();
	}
}

void SideMenu::hide_message1()
{
	message1_enable = false;
}

void SideMenu::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
	window.draw(this->label1);
	window.draw(this->label2);
	window.draw(this->playerThumbnail);
	window.draw(this->playerThumbnail_w);
	window.draw(this->playerThumbnail_b);
	window.draw(this->num_w);
	window.draw(this->num_b);
	if (message1_enable)
		window.draw(this->message1);
}