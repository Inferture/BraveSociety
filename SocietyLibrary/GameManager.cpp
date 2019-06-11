#include "stdafx.h"
#include "GameManager.h"
#include "myMain.h"
#include <iostream>
#include "ColorManipulation.h"
#include "XMLManipulation.h"
using std::cout;
GameManager::GameManager(): selectedMember(-1), selectedInfra(-1)
{
}



void GameManager::UpdateAll()
{
	deltaTime = timer.getElapsedTime().asMilliseconds() / 1000.0f;
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
	for (auto& mem: members)
	{
		if (mem.second.get())
		{
			mem.second->Update();
		}
	}
	for (auto& mem : members)
	{
		if (!mem.second.get() && !Contains(membersToErase,mem.first))
		{
			EraseMember(mem.first);
		}
	}
	for (int i = membersToErase.size() - 1; i >= 0; i--)
	{
		members.erase(membersToErase[i]);
		
		for (auto& mem : members)
		{
			if (mem.second.get() && mem.second->GetTargetMember() == membersToErase[i])
			{
				mem.second->SetTargetMember(-1);
			}
		}
		
		if (selectedMember == membersToErase[i])
		{
			selectedMember = -1;
		}
		membersToErase.pop_back();
	}

	
	for (auto& inf : infrastructures)
	{
		inf.second.get()->Update();
	}
	
	if (selectedMember >= 0)
	{
		members[selectedMember].get()->Handle();
	}
	else if (selectedInfra >= 0)
	{
		infrastructures[selectedInfra].get()->Handle();
	}

	if (saving)
	{
		pugi::xml_document saveDoc(Serialize());
		saveDoc.save_file("./Saves/save.xml");
		saving = false;
	}

	timer.restart();
}

void GameManager::HandleObjectAt(float mouse_x, float mouse_y)
{

	for (auto& mem: members)
	{
		if (mem.second.get()->IsTouched(mouse_x, mouse_y))
		{
			selectedInfra = -1;
			selectedMember = mem.first;
		}
	}
	for (auto& inf : infrastructures)
	{
		if (inf.second.get()->IsTouched(mouse_x, mouse_y))
		{
			selectedInfra = inf.first;
			selectedMember = -1;
		}
	}
}

//Main clock
sf::Clock GameManager::GetTimer() const
{
	return timer;
}
void GameManager::Save() const
{
	saving = true;
}


//All objects of the game
std::vector<GameObject*> GameManager::GetGameObjects() const
{
	return gameObjects;
}

void GameManager::EraseMember(int memberid)
{
	membersToErase.push_back(memberid);
}




//Time elapsed since the last frame
float GameManager::GetDeltaTime() const
{
	return deltaTime;
}

void GameManager::AddMember(Member& member)
{
	members.insert({ member.GetId(), std::make_unique<Member>(member) });
}

void GameManager::AddInfrastructure(Infrastructure& infrastructure) {
	infrastructures.insert({ infrastructure.GetId(), std::make_unique<Infrastructure>(infrastructure) });
}

void GameManager::GenerateMember(int parent1, int parent2)
{
	float redAffiliation = (float)rand() / RAND_MAX;
	float blueAffiliation = (float)rand() / RAND_MAX;
	float tolerance = (float)rand() / RAND_MAX;
	float aggressiveness = (float)rand() / RAND_MAX;


	int hairstyle(dice(texturesHair.size()) - 1);
	sf::Sprite spriteHair;
	spriteHair.setTexture(texturesHair[hairstyle]);

	int bodystyle(dice(texturesBody.size()) - 1);
	sf::Sprite spriteBody;
	spriteBody.setTexture(texturesBody[bodystyle]);

	spriteHair.setColor(RandomColor());
	spriteBody.setColor(RandomSkinColor());

	int clothesstyle(dice(texturesClothes.size()) - 1);
	sf::Sprite spriteClothes;
	spriteClothes.setTexture(texturesClothes[clothesstyle]);

	int stickstyle(dice(texturesStick.size()) - 1);
	sf::Sprite spriteStick;
	spriteStick.setTexture(texturesStick[stickstyle]);

	spriteStick.setColor(sf::Color::White);
	spriteBody.setColor(RandomSkinColor());

	spriteClothes.setColor(AttributeClothesColor(blueAffiliation,redAffiliation));

	Member member(dice(WINDOW_WIDTH), dice(WINDOW_HEIGHT), 0, RandomName(), aggressiveness, tolerance,blueAffiliation, redAffiliation,
		spriteHair, spriteBody, spriteStick, spriteClothes, hairstyle, bodystyle, clothesstyle, stickstyle);
	
	AddMember(member);
}

GameManager::GameManager(pugi::xml_node node) : 
	selectedMember(node.attribute("selectedMember").as_int()), 
	selectedInfra(node.attribute("selectedInfra").as_int()),
	deltaTime(node.attribute("deltaTime").as_float())
{
	pugi::xml_node childNode(node.first_child());

	while (childNode)
	{

		if (!std::strcmp(childNode.name(), "Member"))
		{
			Member mem(childNode);
			members.insert({ mem.GetId(), std::make_unique<Member>(mem) });
		}
		else if (!std::strcmp(childNode.name(), "Infrastructure"))
		{
			Infrastructure infra(childNode);
			infrastructures.insert({ infra.GetId(), std::make_unique<Infrastructure>(infra) });
		}
		childNode = childNode.next_sibling();
	}
}
pugi::xml_document GameManager::Serialize() const
{
	pugi::xml_document doc;
	doc.set_name("ManagerDoc");

	pugi::xml_node node;
	node = doc.append_child("Party");

	pugi::xml_attribute attDeltaTime = node.append_attribute("deltaTime");
	attDeltaTime.set_value(deltaTime);

	pugi::xml_attribute attSelectedMember = node.append_attribute("selectedMember");
	attSelectedMember.set_value(selectedMember);

	pugi::xml_attribute attSelectedInfra = node.append_attribute("selectedInfra");
	attSelectedInfra.set_value(selectedInfra);

	for (auto& mem : members)
	{
		pugi::xml_document memberDoc = mem.second.get()->Serialize();
		add_child(doc, memberDoc);
	}
	for (auto& inf : infrastructures)
	{
		pugi::xml_document memberDoc = inf.second.get()->Serialize();
		add_child(doc, memberDoc);
	}
	return doc;

}
std::string RandomName()
{
	std::vector<std::string> voyels{ "a","e","u","i","y" };

	std::vector<std::string> consonants{ "z","r","t","p","q","s","d","f","g","h","j","k","l","m","w","x","c",
		"v","b","n","tr","dr","gr","sr","sl","pr","br","bl","gl","z","ch","sh","pf","pl","zr","gg","zz","kl",
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