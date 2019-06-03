#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Member.h"
#include <vector>
#include <chrono>
#include <random>

class GameManager
{
private:
	//Main clock
	sf::Clock timer;
	//All objects of the game
	std::vector<GameObject*> gameObjects;
	//All members of the game
	std::vector<Member*> members;
	//Time elapsed since the last frame in seconds
	float deltaTime;
public:
	
	//Main clock
	sf::Clock GetTimer() const;
	//All objects of the game
	std::vector<GameObject*> GetGameObjects() const;
	//All members of the game
	std::vector<Member*> GetMembers() const;
	//Time elapsed since the last frame
	float GetDeltaTime() const;
	//Create a member
	void AddMember(Member* member);
	//Called every frame;
	void UpdateAll();

};
