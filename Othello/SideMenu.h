#pragma once
#include "ObiektGraficzny.h"
#include "circleTexture.h"
#include "Field.h"

struct numberOfPawns {
	int blacks{ 2 };
	int whites{ 2 };
	void update(std::vector <Field*> &FieldTab)
	{
		int b = 0, w = 0;
		for (Field *F : FieldTab)
		{
			if (F->Get() == p1)
				b++;
			if (F->Get() == p2)
				w++;
		}
		blacks = b;
		whites = w;
		//std::cout << "Number of pawns: black " << blacks << ", white " << whites << std::endl;
	}
};

class SideMenu : public ObiektGraficzny
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

public:

	SideMenu();
	~SideMenu();
	void setLabels();
	void update(State curPlayer, numberOfPawns numberOfPawns);
	void show_message1(std::string mode, State);
	void update_clock_message1();
	void hide_message1();
	void draw(sf::RenderWindow& window);
};

