#ifndef __j1Cutscene_H__
#define __j1Cutscene_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Timer.h"
#include <list>
using namespace std; 

struct Action 
{
public:

	int		actor = 0;		//Actor playing the action. 
	int		x = 0;			//Position X the actor needs to reach.
	int		y = 0;			//Position Y the actor needs to reach. 
	uint	speed = 0;		//Actor speed. 
	uint	time = 0;		//Time the action will start.
};

class j1Cutscene :public j1Module
{
public:

	j1Cutscene();
	~j1Cutscene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


public:

	void LoadData(pugi::xml_node& data, uint id);									//Function that loads data from the XML. 
	void Destination(int x, int y, uint speed, iPoint &actor_pos, Action &actor);	//Destination of the actor. 
	void DoAction(list<Action> &actions, Action &actor);							//Adds action to the list

	list <Action> actions_1;
	list <Action> actions_2;

	//TODO 1: (uncomment the line below)
	Action iterator;
	Action actor_1;
	Action actor_2;

	pugi::xml_document cutscenes_xml;

	bool all_loaded = false; 
	
	//Timer
	j1Timer	act_time; 
	int count_time = 0; 
};

#endif // __j1Cutscene_H__
