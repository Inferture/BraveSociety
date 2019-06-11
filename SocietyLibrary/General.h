#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <vector>


const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;


class Infrastructure;

//Unique manager of the game
extern GameManager  GM;
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
//Textures of bubbles
extern std::vector<sf::Texture> texturesBubble;
//Textures of houses
extern std::vector<sf::Texture> texturesHouse;