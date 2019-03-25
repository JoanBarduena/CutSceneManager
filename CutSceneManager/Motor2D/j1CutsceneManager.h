#ifndef __j1Cutscene_H__
#define __j1Cutscene_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Timer.h"
#include <list>
using namespace std; 

#define MAX_ACTIONS 15

class Action 
{
public:
	int		id = 0;			//Action id enum.
	int		x = 0;			//Position X the actor needs to reach.
	int		y = 0;			//Position Y the actor needs to reach. 
	int		speed = 0;		//Actor speed. 
	int		time = 0;		//Time the action takes.
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

	void LoadData(pugi::xml_node& data, uint id); //Function that loads data from the XML. 
	void Destination(int x, int y, uint speed); //Destination of the actor. 
	void CheckDestination(int x, int y, uint speed); //Check if the actor has reached the destination. 
	void CheckTime(int time); //Check if the given time has arrived.
	void DoAction(Action actions); // Adds action to the list

	Action actions[MAX_ACTIONS]; 
	int actions_1_iterator = 0;

	Action iterator;
	Action actor_1;
	Action actor_2;

	pugi::xml_document cutscenes_xml;

	bool all_loaded = false; 
	bool next_action = true; 
	
	//Timer
	j1Timer	act_time; 
	bool timer = true;
};

#endif // __j1Cutscene_H__
