#ifndef __j1Cutscene_H__
#define __j1Cutscene_H__

#include "j1Module.h"
#include "p2Point.h"
#include <list>
using namespace std; 

struct Action 
{
public:

	int		actor_x = 0;
	int		actor_y = 0;
	int		actor_speed = 0;

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
	void CheckDestination(int x, int y); //Checking if the actor has reached the destination. 
	void DoAction(); // Adds action to the list

	list <Action*> actions; 
	Action iterator;

	pugi::xml_document cutscenes_xml;

	bool cutting_scene = false; 

	iPoint	destination;

	bool doing_cut = false; 
};

#endif // __j1Cutscene_H__
