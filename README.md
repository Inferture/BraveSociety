# BraveSociety

C++ school project. [(Releases)](https://github.com/Inferture/BraveSociety/releases)

![](./Demo/BraveSociety.gif)
## Current state:

###   Rules:


There are **2 clans** in the village: the **blue** and the **red** clans.
Each villager has a **blue affiliation** and a **red affiliation**. 
They can be strongly affiliated with one, both, or none of the clans.

They also have other statistics: 

**Tolerance** (when interacting, the bigger the difference in affiliation is and the smaller the tolerance is, the
more likely it is that there will be a conflict)

**Aggressiveness** (chances they will try to attack in case of conflict),

**Attack and defense** (if the attacker's attack is higher than the defender's defense, the defender gets killed).

You observe a bunch of villagers who interact with each other. 
You can choose to **kill a villager** at any given moment.

You can choose to **add infrastructures** (Sword shop, Hospital or Tavern).

**Sword shop** increases attack.

**Hospital** increases defense.

Villager stay longer in the **tavern** than in the sword shop or the hospital but the tavern does not currently affects stats.


Villager will interact with each other randomly (which will increase or decrease their affinity with one another).
If a bond is strong enough, they can become **Friend** or even **BFF**. 
If someone kills someone elses Friend, they will get the relation **KillerFriend** and will lose a lot of affinity with the other person.

They will get inside infrastructures randomly.

The current statistics are making it unlikely for villagers to attack each others though (because for this to be likely to happen, they would need both a strong affiliation difference, a low tolerance and a high aggressiveness and a stronger attack, which is a lot to combine).


###   Commands:

**1**: Switch current infrastructure to Sword Shop

**2**: Switch current infrastructure to Hospital

**3**: Switch current infrastructure to Tavern

**Left Click**: Place current infrastructure

**Right click**: Inspect (if done on a member, you can also kill them from the menu)

**F5**: Save

**F7**: Load 
(there is only one save currently)
