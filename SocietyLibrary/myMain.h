#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "stdafx.h"
#include <pugixml.hpp>
#include "GameManager.h"
#include <vector>
int myMain();


const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;



//Unique manager of the game
extern GameManager  GM ;
//Font used for the name tags
extern sf::Font tagfont;

//Textures of hair
extern std::vector<sf::Texture> texturesHair;
//Textures of body
extern std::vector<sf::Texture> texturesBody;
//Textures of clothes
extern std::vector<sf::Texture> texturesClothes;
//Textures of sticks
extern std::vector<sf::Texture> texturesStick;

//Draws a white line from start to end with a given thickness
void SetLine(sf::RectangleShape &line, sf::Vector2f start, sf::Vector2f end, float thickness);

//Draws a random number between 1(included) and n (included)
int dice(int n);

template<typename T>
bool Contains(std::vector<T> v, T element)
{
	for (T e : v)
	{
		if (e == element)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
void Debug(T obj)
{
	std::cout << obj<<std::endl<<std::flush;
}