#include "stdafx.h"

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
using std::string;
using std::cout;
using std::unique_ptr;

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
	Member member(0,0,0,0,0,0,0,spriteHair,spriteBody);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			window.clear(sf::Color(125, 125, 125, 255));
			window.draw(sprite);
			member.Draw(window, member.GetX(), member.GetY());
		}
		window.display();
	}

	return 5;
}


//OTHER STUFF

void SetLine(sf::RectangleShape &line, sf::Vector2f start, sf::Vector2f end, float thickness)
{
	line.setOrigin(0, 0);
	line.setPosition(start);
	float d = std::sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y)*(start.y - end.y));
	line.setSize(sf::Vector2f(d, thickness));
	line.setRotation(-std::atan2(end.x - start.x, end.y - start.y)*180.0f / 3.14159265359f + 90.0f);
}