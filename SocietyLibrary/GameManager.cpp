#include "stdafx.h"
#include "GameManager.h"
#include "myMain.h"
#include <iostream>
#include "ColorManipulation.h"

using std::cout;
GameManager::GameManager(): selectedMember(-1)
{

}

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
	if (selectedMember>=0)
	{
		members[selectedMember].get()->Handle();
	}
	
	timer.restart();
}

void GameManager::HandleObjectAt(float mouse_x, float mouse_y)
{

	for (auto& mem: members)
	{
		if (mem.second.get()->IsTouched(mouse_x, mouse_y))
		{
			selectedMember = mem.first;
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
/*
std::unordered_map<int, unique_ptr<Member>>& GameManager::GetMembers() const
{
	return members;
}
*/
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

void GameManager::AddMember(Member& member)
{
	members.insert({ member.GetId(), std::make_unique<Member>(member) });
	//gameObjects.push_back(member);
}

void GameManager::AddInfrastructure(Infrastructure* infrastructure) {
	infrastructures.push_back(infrastructure);
	gameObjects.push_back(infrastructure);
}

void GameManager::GenerateMember(int parent1, int parent2)
{
	float redAffiliation = (float)rand() / RAND_MAX;
	float blueAffiliation = (float)rand() / RAND_MAX;
	float tolerance = (float)rand() / RAND_MAX;
	float aggressiveness = (float)rand() / RAND_MAX;


	sf::Sprite spriteHair;
	spriteHair.setTexture(texturesHair[dice(texturesHair.size()) - 1]);

	sf::Sprite spriteBody;
	spriteBody.setTexture(texturesBody[dice(texturesBody.size()) - 1]);

	spriteHair.setColor(sf::Color(70, 10, 10));
	spriteBody.setColor(sf::Color(196, 144, 124));
	spriteBody.setColor(RandomSkinColor());


	sf::Sprite spriteClothes;
	spriteClothes.setTexture(texturesClothes[dice(texturesClothes.size()) - 1]);

	sf::Sprite spriteStick;
	spriteStick.setTexture(texturesStick[dice(texturesStick.size()) - 1]);

	spriteStick.setColor(sf::Color::White);
	spriteBody.setColor(RandomSkinColor());

	spriteClothes.setColor(AttributeClothesColor(blueAffiliation,redAffiliation));
	Member member(dice(1000), dice(500), 0, RandomName(), aggressiveness, tolerance,blueAffiliation, redAffiliation, spriteHair, spriteBody, spriteStick, spriteClothes);
	AddMember(member);
}


std::string RandomName()
{
	std::vector<std::string> voyels{ "a","e","u","i","y" };

	std::vector<std::string> consonants{ "z","r","t","p","q","s","d","f","g","h","j","k","l","m","w","x","c",
		"v","b","n","tr","dr","gr","sr","sl","pr","br","bl","gl","z","ch","sh","pf","pl","zr","gg","zz","kl"
	"nm","ps" };

	int sounds = dice(5) + 2;
	bool voyel = dice(2) == 1;
	bool lastVoyel = false;
	std::string name("");
	for (int i = 0; i < sounds; i++)
	{
		if (voyel)
		{
			name += voyels[dice(voyels.size() - 1)];
			if (lastVoyel || dice(2) == 1)
			{
				voyel = false;
			}
			lastVoyel = true;
		}
		else
		{
			lastVoyel = false;
			name += consonants[dice(consonants.size() - 1)];
			voyel = true;
		}
	}
	std::transform(name.begin(), name.begin()+1, name.begin(), ::toupper);
	return name;
}