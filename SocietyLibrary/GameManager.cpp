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
	if (selectedObject)
	{
		selectedObject->Handle();
	}
	
	timer.restart();
}

void GameManager::HandleObjectAt(float mouse_x, float mouse_y)
{

	for (unsigned int i = 0; i < members.size(); i++)
	{
		Member* member = members[i];
		if (member->IsTouched(mouse_x, mouse_y))
		{
			selectedObject = member;
			return;
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

std::vector<Infrastructure*> GameManager::GetInfrastructures() const {
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

