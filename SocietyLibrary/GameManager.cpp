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

	
	timer.restart();
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
}