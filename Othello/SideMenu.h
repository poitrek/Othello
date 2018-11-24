#pragma once
#include "GameObject.h"
#include "Field.h"


class SideMenu : public GameObject
{
private:
	const std::string file_name = "../Othello/Side menu.jpg";
	const std::string font_file_name = "../Othello/CODE bold.otf";
	
	sf::Font textfont;
	sf::Text label1;
	sf::Text label2;
	sf::Text num_b;
	sf::Text num_w;
	sf::Text message1;
	bool message1_enable;
	sf::Clock clock_message1;
	bool clock_message1_enable;
	sf::Sprite playerThumbnail;
	sf::Sprite playerThumbnail_b;
	sf::Sprite playerThumbnail_w;

	void setSpriteSize(sf::Sprite &sprite, sf::Vector2f vec);

public:

	SideMenu();
	~SideMenu();
	void setLabels();
	void update(FieldState curPlayer, std::pair<int, int> numOfPawns);
	void show_message1(std::string mode, FieldState);
	void update_clock_message1();
	void hide_message1();
	void draw(sf::RenderTarget& target);
};

