#include "j1CutsceneManager.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Player.h"
#include <iostream>
using namespace std; 

j1Cutscene::j1Cutscene() : j1Module()
{

}

j1Cutscene::~j1Cutscene()
{
}

bool j1Cutscene::Awake()
{
	return true;
}

bool j1Cutscene::Start()
{
	act_time.Start(); 
	return true;
}

bool j1Cutscene::PreUpdate()
{
	return true;
}

bool j1Cutscene::Update(float dt)
{
	pugi::xml_parse_result res = cutscenes_xml.load_file("cutscenes.xml");;

	pugi::xml_node xml = cutscenes_xml.document_element(); 

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		LoadData(xml, 1);

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		LoadData(xml, 2); 		

	if (cutting_scene)
	{
		DoAction(actions_1);
		DoAction(actions_2);
	}
		
	if (!next_action)
	{
		Destination(destination.x, destination.y, destination.speed); 
		CheckDestination(destination.x, destination.y, destination.speed); 
	}

	if(!timer)
		CheckTime(destination.time);

	return true;
}

bool j1Cutscene::PostUpdate()
{
	return true;
}

bool j1Cutscene::CleanUp()
{
	return true;
}

void j1Cutscene::LoadData(pugi::xml_node& data, uint id)
{
	pugi::xml_node cutscene_id; 
	pugi::xml_node xml_actions;

	for (cutscene_id = data.child("cutscene"); cutscene_id; cutscene_id = cutscene_id.next_sibling("cutscene"))
	{
		if (cutscene_id.attribute("id").as_uint() == id)
		{
			for (xml_actions = cutscene_id.child("action"); xml_actions; xml_actions = xml_actions.next_sibling("action"))
			{
					iterator.x = xml_actions.attribute("pos_x").as_int();
					iterator.y = xml_actions.attribute("pos_y").as_int();
					iterator.speed = xml_actions.attribute("speed").as_int();
					iterator.time = xml_actions.attribute("time").as_int();
					iterator.actor = xml_actions.attribute("actor").as_int(); 

					if(iterator.actor == 1)
						actions_1.push_back(iterator);
					if(iterator.actor == 2)
						actions_2.push_back(iterator);
			}
		}
	}
	cutting_scene = true; 
}

void j1Cutscene::Destination(int x, int y, uint speed) 
{
	if (x > App->player->position.x)
		App->player->position.x += speed;
	else if (x < App->player->position.x)
		App->player->position.x -= speed;
	
	if(App->player->position.x + speed > x > App->player->position.x)
		App->player->position.x == x; 

	if (y > App->player->position.y)
		App->player->position.y += speed;
	else if (y < App->player->position.y)
		App->player->position.y -= speed;

	if (App->player->position.y + speed > y > App->player->position.y)
		App->player->position.y == y;
}

void j1Cutscene::CheckDestination(int x, int y, uint speed)
{
	if (x + speed >= App->player->position.x && x - speed <= App->player->position.x
		&& speed + y >= App->player->position.y && y - speed <= App->player->position.y)
		next_action = true;
}

void j1Cutscene::CheckTime(int time)
{
	if (time == (act_time.Read()/1000)) //Read in seconds.
		timer = true;	
}

void j1Cutscene::DoAction(list <Action> actions)
{
	if(!actions.empty()) // List of actions. 
	{
		if (next_action && timer) // Do not start an action before the previous had finished.
		{
			//Start(); //In order to start the timer again

			next_action = false;
			timer = false;

			destination.x = actions.front().x;
			destination.y = actions.front().y;
			destination.speed = actions.front().speed;
			destination.time = actions.front().time;

			actions.pop_front(); 	
		}	
	}
}

