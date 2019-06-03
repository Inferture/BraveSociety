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
	if (!textureHair.loadFromFile("Sprites/hair.png"))
	{
		cout << "Hair not found";
	}
	spriteHair.setTexture(textureHair);

	sf::Sprite spriteBody;
	sf::Texture textureBody;
	textureBody.setSmooth(true);
	if (!textureBody.loadFromFile("Sprites/body.png"))
	{
		cout << "Body not found";
	}
	spriteBody.setTexture(textureBody);

	spriteHair.setColor(sf::Color(70,10,10));
	spriteBody.setColor(sf::Color(196, 144, 124));

	
	sf::Sprite spriteClothes;
	sf::Texture textureClothes;
	textureClothes.setSmooth(true);
	if (!textureClothes.loadFromFile("Sprites/clothes.png"))
	{
		cout << "Clothes not found";
	}
	spriteClothes.setTexture(textureClothes);

	sf::Sprite spriteStick;
	sf::Texture textureStick;
	textureStick.setSmooth(true);
	if (!textureStick.loadFromFile("Sprites/stick.png"))
	{
		cout << "Stick not found";
	}
	spriteStick.setTexture(textureStick);

	spriteStick.setColor(sf::Color::White);
	spriteClothes.setColor(sf::Color::Red);

	Member member(500,0,0,"Mark",0,0,0,0,spriteHair,spriteBody, spriteStick, spriteClothes);
	sf::Sprite spriteHair2(spriteHair);
	sf::Sprite spriteBody2(spriteBody);
	sf::Sprite spriteStick2(spriteStick);
	sf::Sprite spriteClothes2(spriteClothes);
	spriteClothes2.setColor(sf::Color::Blue);
	Member member2(0, 500, 0, "Pawl", 0, 0, 0, 0, spriteHair2, spriteBody2, spriteStick2, spriteClothes2);
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

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				float mouse_x = sf::Mouse::getPosition().x;
				float mouse_y = sf::Mouse::getPosition().y;
				GM.HandleObjectAt(mouse_x, mouse_y);
			}
		}

		//Update
		GM.UpdateAll();

		//Render
		window.clear(sf::Color(125, 125, 125, 255));
		std::vector<Member*> members(GM.GetMembers());
		for (unsigned int i = 0; i < members.size(); i++)
		{
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

