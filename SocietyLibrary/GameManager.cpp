#include "stdafx.h"
#include "GameManager.h"


void GameManager::UpdateAll()
{
	deltaTime = timer.getElapsedTime().asMilliseconds() / 1000.0f;
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
	for (unsigned int i = 0; i < members.size(); i++)
	{
		members[i]->Update();
	}
	for (unsigned int i = 0; i < infrastructures.size(); i++)
	{
		infrastructures[i]->Update();
	}
	
	timer.restart();
}

void GameManager::HandleObjectAt(float mouse_x, float mouse_y)
{
	for (unsigned int i = 0; i < members.size(); i++)
	{
		Member* member = members[i];
		float delta_x(member->GetX()-mouse_x);
		float delta_y(member->GetY() - mouse_y);
		if (delta_x*delta_x + delta_y*delta_y < 0)
		{

		}
	}
}

//Main clock
sf::Clock GameManager::GetTimer() const
{
	return timer;
}

//All members of the game
std::vector<Member*> GameManager::GetMembers() const
{
	return members;
}

//All infrastructures of the game
std::vector<Infrastructure*> GameManager::GetInfrastructures() const
{
	return infrastructures;
}

//All objects of the game
std::vector<GameObject*> GameManager::GetGameObjects() const
{
	return gameObjects;
}

//Time elapsed since the last frame
float GameManager::GetDeltaTime() const
{
	return deltaTime;
}

void GameManager::AddMember(Member* member)
{
	members.push_back(member);
	gameObjects.push_back(member);
}

void GameManager::AddInfrastructure(Infrastructure* infrastructure) 
{
	infrastructures.push_back(infrastructure);
	gameObjects.push_back(infrastructure);
}