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
#include <set>
using std::string;
using std::cout;
using std::unique_ptr;



GameManager GM;
sf::Font tagfont;

std::vector<sf::Texture> texturesHair;
std::vector<sf::Texture> texturesBody;
std::vector<sf::Texture> texturesClothes;
std::vector<sf::Texture> texturesStick;
std::vector<sf::Texture> texturesBubble;
std::vector<sf::Texture> texturesHouse;

int currentInfrastructure=1;
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
	if (!textureHair.loadFromFile("Sprites/hair2.png"))
	{
		cout << "Hair not found";
	}
	texturesHair.push_back(textureHair);
	if (!textureHair.loadFromFile("Sprites/hair3.png"))
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

	sf::Texture textureBubble;
	textureBubble.setSmooth(true);
	if (!textureBubble.loadFromFile("Sprites/bubble.png"))
	{
		cout << "Bubble not found";
	}
	texturesBubble.push_back(textureBubble);

	sf::Texture textureHouse;
	textureHouse.setSmooth(true);
	if (!textureHouse.loadFromFile("Sprites/house.png"))
	{
		cout << "House not found";
	}
	texturesHouse.push_back(textureHouse);

	sf::Sprite spriteBackground;
	sf::Texture textureBackground;
	textureBackground.setSmooth(true);
	if (!textureBackground.loadFromFile("Sprites/background.png"))
	{
		cout << "Background not found";
	}
	spriteBackground.setTexture(textureBackground);

	sf::Sprite spriteInfrastructure;
	sf::Texture textureInfrastructure;
	textureInfrastructure.setSmooth(true);
	if (!textureInfrastructure.loadFromFile("Sprites/house.png"))
	{
		cout << "House not found";
	}
	spriteInfrastructure.setTexture(textureInfrastructure);

	spriteInfrastructure.setColor(sf::Color::Red);
	Infrastructure house(50, 150, 0, "Sword shop", 0,1,3, spriteInfrastructure,10);
	
	sf::Sprite spriteInfrastructure2;
	spriteInfrastructure2.setTexture(textureInfrastructure);

	spriteInfrastructure2.setColor(sf::Color::Blue);
	Infrastructure house2(1600, 700, 0, "Hospital" ,1, 0, 3, spriteInfrastructure2, 10);

	sf::Sprite spriteInfrastructure3;
	spriteInfrastructure3.setTexture(textureInfrastructure);
	spriteInfrastructure3.setColor(sf::Color::Yellow);


	GM.AddInfrastructure(house);
	GM.AddInfrastructure(house2);

	GM.GenerateMember(-1,-1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	GM.GenerateMember(-1, -1);
	bool flagMouseDown(false);
	GM.UpdateAll();//
	
	//Loop
	while (window.isOpen())
	{
		sf::Event event;

		ImGui::SFML::Update(window, deltaClock.restart());

		//Events
		while (window.pollEvent(event))
		{

			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				currentInfrastructure = 1;
			}
			if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				currentInfrastructure = 2;
			}
			if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				currentInfrastructure = 3;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !flagMouseDown)
			{
				float mouse_x = (float)sf::Mouse::getPosition().x;
				float mouse_y = (float)sf::Mouse::getPosition().y;

				float tx = textureInfrastructure.getSize().x;
				float ty = textureInfrastructure.getSize().y;

				if (currentInfrastructure == 1)
				{
					Infrastructure swordShop(mouse_x-tx/2, mouse_y-ty/2, 0, "Sword shop", 0, 1, 3, spriteInfrastructure, 10);
					GM.AddInfrastructure(swordShop);
				}
				if (currentInfrastructure == 2)
				{
					Infrastructure hospital(mouse_x - tx / 2, mouse_y - ty / 2, 0, "Hospital", 1, 0, 3, spriteInfrastructure2, 10);
					GM.AddInfrastructure(hospital);
				}
				if (currentInfrastructure == 3)
				{
					Infrastructure tavern(mouse_x - tx / 2, mouse_y - ty / 2,0, "Tavern", 0, 0, 3, spriteInfrastructure3, 20);
					GM.AddInfrastructure(tavern);
				}
				flagMouseDown = true;
			}
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				flagMouseDown = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				float mouse_x = (float)sf::Mouse::getPosition().x;
				float mouse_y = (float)sf::Mouse::getPosition().y;
				GM.HandleObjectAt(mouse_x, mouse_y);
			}
			if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
			{
				GM.Save();
			}
			if (sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::F7))
			{
				pugi::xml_document doc;
				pugi::xml_parse_result result = doc.load_file("./Saves/save.xml");
				GM = GameManager(doc.first_child());
				for (auto& mem : GM.members)
				{
					mem.second.get()->GetId();
				}
				for (auto& infra : GM.infrastructures)
				{
					infra.second.get()->GetId();
				}
			}
			
		}
		

		
		//Update
		GM.UpdateAll();
		//Render
		window.clear(sf::Color(125, 125, 125, 255));
		window.draw(spriteBackground);
		//ImGui::SFML::Render(window);

		std::vector<std::pair<float, int>> membersSort;
		std::vector<std::pair<float, int>> infrastructuresSort;
		for (auto& mem : GM.members)
		{
			membersSort.push_back(std::make_pair( mem.second.get()->GetY(), mem.second.get()->GetId() ));
		}
		for (auto& infra : GM.infrastructures)
		{
			infrastructuresSort.push_back({ infra.second.get()->GetY(), infra.second.get()->GetId() });
		}

		std::sort(membersSort.begin(), membersSort.end(),Sort);
		std::sort(infrastructuresSort.begin(), infrastructuresSort.end(), Sort);


		int m(0);
		int i(0);
		while (m < membersSort.size() || i < infrastructuresSort.size())
		{
			if (m < membersSort.size() && i < infrastructuresSort.size())
			{
				if (GM.infrastructures[infrastructuresSort[i].second].get()->GetY() < GM.members[membersSort[m].second].get()->GetY())
				{
					GM.infrastructures[infrastructuresSort[i].second].get()->Draw(window, GM.infrastructures[infrastructuresSort[i].second].get()->GetX(), GM.infrastructures[infrastructuresSort[i].second].get()->GetY(), false);
					i++;
				}
				else
				{
					GM.members[membersSort[m].second].get()->Draw(window, GM.members[membersSort[m].second].get()->GetX(), GM.members[membersSort[m].second].get()->GetY(), false);
					m++;
				}
			}
			else if (m < membersSort.size())
			{
				GM.members[membersSort[m].second].get()->Draw(window, GM.members[membersSort[m].second].get()->GetX(), GM.members[membersSort[m].second].get()->GetY(), false);
				m++;
			}
			else
			{
				GM.infrastructures[infrastructuresSort[i].second].get()->Draw(window, GM.infrastructures[infrastructuresSort[i].second].get()->GetX(), GM.infrastructures[infrastructuresSort[i].second].get()->GetY(), false);
				i++;
			}
		}

		ImGui::SFML::Render(window);
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

//Sorts pairs with the first value
bool Sort(std::pair<float, int>a, std::pair<float, int>b)
{
	return a.first < b.first;
}
