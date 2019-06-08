#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Member.h"
#include "infrastructure.h"
#include <vector>
#include <chrono>
#include <random>
#include <unordered_map>
class GameManager
{
private:
	//Main clock
	sf::Clock timer;
	//All objects of the game
	std::vector<GameObject*> gameObjects;
	
	
	//All infratructures of the game
	std::vector<Infrastructure*> infrastructures;
	//Time elapsed since the last frame in seconds
	float deltaTime;
	int selectedMember;
public:
	GameManager();
	//All members of the game
	std::unordered_map<int, unique_ptr<Member>> members;

	//Main clock
	sf::Clock GetTimer() const;
	//All objects of the game
	std::vector<GameObject*> GetGameObjects() const;
	//All members of the game
	//std::unordered_map<int, unique_ptr<Member>>& GetMembers() const;
	//All infrastructures of the game
	std::vector<Infrastructure*> GetInfrastructures() const;
	//Time elapsed since the last frame
	float GetDeltaTime() const;
	//Create a member
	void AddMember(Member& member);
	//Create an infrastructure
	void AddInfrastructure(Infrastructure* infrastructure);
	//Called every frame;
	void UpdateAll();
	//Opens the window for the object clicked
	void HandleObjectAt(float mouse_x, float mouse_y);

	void GenerateMember(int parent1=-1, int parent2=-1);

	
};
std::string RandomName();