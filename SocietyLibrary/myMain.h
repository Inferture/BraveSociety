#pragma once
#include "stdafx.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <vector>
#include "General.h"
int myMain();




//Draws a white line from start to end with a given thickness
void SetLine(sf::RectangleShape &line, sf::Vector2f start, sf::Vector2f end, float thickness);

//Draws a random number between 1(included) and n (included)
int dice(int n);

//Sorts by first element of the pair
bool Sort(std::pair<float, int>a, std::pair<float, int>b);

//Returns true if the element if found in the vector v
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

/*
//Prints something in real time, for debugging purpose, not needed in final version
template<typename T>
void Debug(T obj)
{
	std::cout << obj<<std::endl<<std::flush;
}*/