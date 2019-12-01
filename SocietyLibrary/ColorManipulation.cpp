#include "stdafx.h"
#include "ColorManipulation.h"
#include <imgui.h>
using std::string;

///All the functions to manipulate color


///<summary>
///Generate a string from a color for serialization
///</summary>
///<param name="color">color to convert to string</param>
std::string GetColorString(sf::Color color)
{
	if (color == sf::Color::Blue)
	{
		return "Blue";
	}
	if (color == sf::Color::White)
	{
		return "White";
	}
	if (color == sf::Color::Green)
	{
		return "Green";
	}
	if (color == sf::Color::Red)
	{
		return "Red";
	}
	if (color == sf::Color::Yellow)
	{
		return "Yellow";
	}
	if (color == sf::Color::Magenta)
	{
		return "Magenta";
	}
	if (color == sf::Color::Cyan)
	{
		return "Cyan";
	}
	if (color == sf::Color::Transparent)
	{
		return "Transparent";
	}
	if (color == sf::Color::Black)
	{
		return "Black";
	}
	
	string s;
	s.append(stringHex(color.r));
	s.append(stringHex(color.g));
	s.append(stringHex(color.b));
	return s;

}

///<summary>
///Finds the color corresponding to a given string
///Either a string corresponding to a preset Color ("Blue")
///or a hex string representing an rgb code (ff0000 for red)
///for example
///</summary>
///<param name="color">string to convert to color</param>
sf::Color GetStringColor(std::string color)
{
	if (color._Equal("Blue"))
	{
		return sf::Color::Blue;
	}
	if (color._Equal("White"))
	{
		return sf::Color::White;
	}
	if (color._Equal("Green"))
	{
		return sf::Color::Green;
	}
	if (color._Equal("Red"))
	{
		return sf::Color::Red;
	}
	if (color._Equal("Yellow"))
	{
		return sf::Color::Yellow;
	}
	if (color._Equal("Magenta"))
	{
		return sf::Color::Magenta;
	}
	if (color._Equal("Cyan"))
	{
		return sf::Color::Cyan;
	}
	if (color._Equal("Transparent"))
	{
		return sf::Color::Transparent;
	}
	if (color._Equal("Black"))
	{
		return sf::Color::Black;
	}

	if (color.size() == 6)
	{
		return sf::Color(hexString(color.substr(0, 2)), hexString(color.substr(2, 2)), hexString(color.substr(4, 2)));
	}
	return sf::Color::Black;
}


///<summary>
///A small variation from a color to indicate it
///has been selected. For example, for making an
///outline of the object of said color
///</summary>
///<param name="color">base color</param>
sf::Color GetColorSelected(sf::Color color)
{
	if (color.r + color.g + color.b <= 255 * 3 / 2)
	{
		float m1(256.0f / std::max({ color.r + 1,color.g + 1,color.b + 1 }));
		float m2((171.0f) / std::min({ color.r + 1,color.g + 1,color.b + 1 }));//170=255*2/3
		float m(std::min(m1, m2));
		return sf::Color((int)((color.r + 1)*m), (int)((color.g + 1)*m), (int)((color.b + 1)*m));
	}
	else
	{
		sf::Color c2(sf::Color(256 - color.g, 256 - color.g, 256 - color.b));
		float m1(255.0f / std::max({ c2.r,c2.g,c2.b }));
		float m2((171.0f) / std::min({ color.r,color.g,color.b }));//170=255*2/3
		float m(std::min(m1, m2));
		return sf::Color(255 - (int)(c2.r*m), 255 - (int)(c2.g*m), 255 - (int)(c2.b*m));
	}
}

///<summary>
///Converts an int between 0 and 255 to a string
///representing its value in base 16
///</summary>
///<param name="a">int to convert (should be between 0 and 255)</param>
std::string stringHex(int a)
{
	string s("");
	int d = (a / 16) % 16;
	int b = a % 16;
	
	string values[]{ "0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f" };
	s.append(values[d]);
	s.append(values[b]);

	return s;
}

///<summary>
///Gets the value of a string representing an hexadecimal number
///Example: fe for 254
///</summary>
///<param name="a">string representing an hexadecimal number</param>
int hexString(std::string a)
{
	unsigned int i(0);
	int n(0);
	while (i < a.size())
	{

		n *= 16;
		switch (a[i])
		{
		case '0':
			break;
		case '1':
			n += 1;
			break;
		case '2':
			n += 2;
			break;
		case '3':
			n += 3;
			break;
		case '4':
			n += 4;
			break;
		case '5':
			n += 5;
			break;
		case '6':
			n += 6;
			break;
		case '7':
			n += 7;
			break;
		case '8':
			n += 8;
			break;
		case '9':
			n += 9;
			break;
		case 'a':
			n += 10;
			break;
		case 'b':
			n += 11;
			break;
		case 'c':
			n += 12;
			break;
		case 'd':
			n += 13;
			break;
		case 'e':
			n += 14;
			break;
		case 'f':
			n += 15;
			break;
		default:
			return n / 16;
		}
		i++;
	}
	return n;
}

///<summary>
///Generates a random skin color
///</summary>
sf::Color RandomSkinColor()
{
	//255,200,125
	float r = ((float)rand() / (RAND_MAX))*128+ 128;
	float g = r * 200.0f / 255.0f;
	float b = r * 125.0f / 255.0f;
	return sf::Color((int)r, (int)g, (int)b);
}
///<summary>
///Generates a random color
///</summary>
sf::Color RandomColor()
{
	float r = ((float)rand() / (RAND_MAX)) * 255;
	float g = ((float)rand() / (RAND_MAX)) * 255;
	float b = ((float)rand() / (RAND_MAX)) * 255;
	return sf::Color((int)r, (int)g, (int)b);
}

///<summary>
///Generates a color from the blue affiliation and the
///red affiliation of a member to put on their clothes
///</summary>
///<param name="blueAffiliation">blue affiliation of the member</param>
///<param name="redAffiliation">red affiliation of the member</param>
sf::Color AttributeClothesColor(float blueAffiliation, float redAffiliation) {
	float r = 255 * redAffiliation;
	float b = 255 * blueAffiliation;
	return sf::Color((int)r, 0, (int)b);
}

///<summary>
///Converts an sf::Color to an ImColor
///</summary>
///<param name="color">sf::Color to convert</param>
ImColor SfToImColor(sf::Color color)
{
	return ImColor(color.r, color.g, color.b, color.a);
}