#include "stdafx.h"
#include <random>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <pugixml.hpp>
#include <algorithm>
#include <imgui.h>
#include <sfml-imgui/imgui-SFML.hpp>
#include "myMain.h"
#include "GameObject.h"
#include "Member.h"
#include "GameManager.h"
using std::string;
using std::cout;
using std::unique_ptr;

GameManager GM;

int myMain()
{
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Brave Society");

	window.setFramerateLimit(60);


	sf::Sprite sprite;
	sf::Texture texture;
	texture.setSmooth(true);
	if (!texture.loadFromFile("Sprites/Hamster.png"))
	{
		cout << "Hamster not found";
	}
	sprite.setTexture(texture);

	sf::Sprite spriteHair;
	sf::Texture textureHair;
	textureHair.setSmooth(true);
	if (!textureHair.loadFromFile("Sprites/hair0.png"))
	{
		cout << "Hair not found";
	}
	spriteHair.setTexture(textureHair);
	sf::Sprite spriteBody;
	sf::Texture textureBody;
	textureBody.setSmooth(true);
	if (!textureBody.loadFromFile("Sprites/body0.png"))
	{
		cout << "Body not found";
	}
	spriteBody.setTexture(textureBody);

	spriteHair.setColor(sf::Color::Blue);
	spriteBody.setColor(sf::Color::Magenta);
	Member member(0,0,0,"Mark",0,0,0,0,spriteHair,spriteBody);
	sf::Sprite spriteHair2(spriteHair);
	sf::Sprite spriteBody2(spriteBody);
	Member member2(500, 500, 0, "Pawl", 0, 0, 0, 0, spriteHair2, spriteBody2);
	GM.AddMember(&member);
	GM.AddMember(&member2);
	GM.UpdateAll();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		//Update
		GM.UpdateAll();

		//Render
		window.clear(sf::Color(125, 125, 125, 255));
		std::vector<Member*> members(GM.GetMembers());
		for (unsigned int i = 0; i < members.size(); i++)
		{
			/*cout << "\nX:"<<members[i]->GetX();
			cout << "\nY:"<<members[i]->GetY();
			cout << "\nhairX:" << members[i]->hair.getPosition().x;
			cout << "\nhairY:" << members[i]->GetY();*/
			members[i]->Draw(window, members[i]->GetX(), members[i]->GetY());
		}
		//manager.UpdateAll();

		//window.draw(sprite);
		//member.Draw(window, member.GetX(), member.GetY());
		window.display();
	}

	return 5;
}


//OTHER STUFF\\


//Draws a white line from start to end with a given thickness
void SetLine(sf::RectangleShape &line, sf::Vector2f start, sf::Vector2f end, float thickness)
{
	line.setOrigin(0, 0);
	line.setPosition(start);
	float d = std::sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y)*(start.y - end.y));
	line.setSize(sf::Vector2f(d, thickness));
	line.setRotation(-std::atan2(end.x - start.x, end.y - start.y)*180.0f / 3.14159265359f + 90.0f);
}


//Draws a random number between 1(included) and n (included)
int dice(int n)
{
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(1, n);
	return distribution(engine);
}

