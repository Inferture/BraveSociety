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
#include "Member.h"
#include "GameManager.h"
#include "ColorManipulation.h"
#include "SFML/Graphics.hpp"
using std::string;
using std::cout;
using std::unique_ptr;

GameManager GM;
sf::Font tagfont;

std::vector<sf::Texture> texturesHair;
std::vector<sf::Texture> texturesBody;
std::vector<sf::Texture> texturesClothes;
std::vector<sf::Texture> texturesStick;


int myMain()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Brave Society");

	tagfont.loadFromFile("Fonts/Augusta.ttf");

	sf::Clock deltaClock;
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	
	sf::Texture textureHair;
	textureHair.setSmooth(true);
	if (!textureHair.loadFromFile("Sprites/hair.png"))
	{
		cout << "Hair not found";
	}
	texturesHair.push_back(textureHair);


	sf::Texture textureBody;
	textureBody.setSmooth(true);
	if (!textureBody.loadFromFile("Sprites/body.png"))
	{
		cout << "Body not found";
	}
	texturesBody.push_back(textureBody);

	
	sf::Texture textureClothes;
	textureClothes.setSmooth(true);
	if (!textureClothes.loadFromFile("Sprites/clothes.png"))
	{
		cout << "Clothes not found";
	}
	texturesClothes.push_back(textureClothes);


	sf::Texture textureStick;
	textureStick.setSmooth(true);
	if (!textureStick.loadFromFile("Sprites/stick.png"))
	{
		cout << "Stick not found";
	}
	texturesStick.push_back(textureStick);


	sf::Sprite spriteInfrastructure;
	sf::Texture textureInfrastructure;
	textureInfrastructure.setSmooth(true);
	if (!textureInfrastructure.loadFromFile("Sprites/house.png"))
	{
		cout << "House not found";
	}
	spriteInfrastructure.setTexture(textureInfrastructure);

	spriteInfrastructure.setColor(sf::Color::Red);
	Infrastructure house(50, 150, 0, "House", 0, 0, 5, spriteInfrastructure);
	GM.AddInfrastructure(&house);


	GM.GenerateMember(-1,-1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	bool flagMouseDown(false);
	GM.UpdateAll();//
	
	while (window.isOpen())
	{
		sf::Event event;

		ImGui::SFML::Update(window, deltaClock.restart());
		while (window.pollEvent(event))
		{

			ImGui::SFML::ProcessEvent(event);
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
		ImGui::SFML::Render(window);

		std::vector<Infrastructure*> infrastructures(GM.GetInfrastructures());
		infrastructures[0]->Draw(window, infrastructures[0]->GetX(), infrastructures[0]->GetY(), false);
		
		for (auto& mem : GM.members)
		{
			mem.second.get()->Draw(window, mem.second.get()->GetX(), mem.second.get()->GetY(), false);
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

