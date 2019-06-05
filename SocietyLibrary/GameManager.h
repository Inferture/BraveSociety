#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Member.h"
#include "infrastructure.h"
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
	//All infrastructures of the game
	std::vector<Infrastructure*> infrastructures;
	//Time elapsed since the last frame in seconds
	float deltaTime;
public:
	


	//All objects of the game
	std::vector<GameObject*> GetGameObjects() const;
	//All members of the game
	std::vector<Member*> GetMembers() const;
	//All infrastructures of the game
	std::vector<Infrastructure*> GetInfrastructures() const;

	//Create a member
	void AddMember(Member* member);
	//Create an infrastructure
	void AddInfrastructure(Infrastructure* infrastructure);

	//Main clock
	sf::Clock GetTimer() const;
	//Time elapsed since the last frame
	float GetDeltaTime() const;
	//Called every frame;
	void UpdateAll();
	//Opens the window for the object clicked
	void HandleObjectAt(float mouse_x, float mouse_y);
};
