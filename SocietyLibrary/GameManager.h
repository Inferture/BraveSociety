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


class Infrastructure;

class GameManager
{
private:
	//Main clock
	sf::Clock timer;
	//All objects of the game
	std::vector<GameObject*> gameObjects;
	//Time elapsed since the last frame in seconds
	float deltaTime;
	//Member currently selected (to display info/interaction window)
	int selectedMember;
	//Infrastructure currently selected (to display info/interaction window)
	int selectedInfra;
	//Members about to be erased (either dead or in an infrastructure)
	std::vector<int> membersToErase;
	//Are we currently saving ?
	mutable bool saving;
public:
	GameManager();
	GameManager(pugi::xml_node node);
	//All members of the game
	std::unordered_map<int, unique_ptr<Member>> members;

	//All infratructures of the game
	std::unordered_map<int, unique_ptr<Infrastructure>> infrastructures;
	//Main clock
	sf::Clock GetTimer() const;
	//All objects of the game
	std::vector<GameObject*> GetGameObjects() const;
	//All members of the game
	//std::unordered_map<int, unique_ptr<Member>>& GetMembers() const;
	//All infrastructures of the game
	//std::vector<Infrastructure*> GetInfrastructures() const;
	//Time elapsed since the last frame
	float GetDeltaTime() const;
	//Create a member
	void AddMember(Member& member);
	//Create an infrastructure
	void AddInfrastructure(Infrastructure& infrastructure);
	//Called every frame;
	void UpdateAll();
	//Opens the window for the object clicked
	void HandleObjectAt(float mouse_x, float mouse_y);
	//Generates a member with random characteristics
	void GenerateMember(int parent1=-1, int parent2=-1);
	//Erase the member with the id MemberId
	void EraseMember(int memberId);
	//Serializes the manager with all the infrastructures and members for saving
	pugi::xml_document Serialize() const;
	//Save the party ? (erases previous save)
	void Save() const;
};
//Generates a random supposedly pronouncable name
std::string RandomName();

