#pragma once
#include <SFML/Graphics.hpp>
#include <string>
/*
Takes a string of either a base sf Color (ex:"Red")
or the hexCode of the color (ex:ff0000) and returns
the appropriate color
*/
sf::Color GetStringColor(std::string color);
/*
Takes a color and makes a sting out of it, either
the name of the color for base colors ("Blue" for
sf::Color::Blue) or the hexCode of the color
*/
std::string GetColorString(sf::Color color);

/*
returns the value of the hexadecimal string
Precondition: a is composed of numbers [0,9] and
letters from a to f (lower case)
*/
int hexString(std::string a);
/*
returns a string with the last 2 characters of
the hexadecimal value of a
*/
std::string stringHex(int a);

//A random skin color
sf::Color RandomSkinColor();

//Attribute the right color according to the team affiliation
sf::Color AttributeClothesColor(float blueAffiliation, float RedAffiliation);