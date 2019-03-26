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
	{
		LoadData(xml, 1);
		act_time.Start(); 
	}
		
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		LoadData(xml, 2);
		act_time.Start();
	}
			

	if (all_loaded)	//Attributes loaded of the cutscene pressed.
	{
		DoAction(actions_1, actor_1);	
		DoAction(actions_2, actor_2);
		Destination(actor_1.x, actor_1.y, actor_1.speed, App->player->position, actor_1);
		Destination(actor_2.x, actor_2.y, actor_2.speed, App->player->position2, actor_2);
	}

	count_time = act_time.Read() / 1000; 

	return true;
}

bool j1Cutscene::PostUpdate()
{
	return true;
}

bool j1Cutscene::CleanUp()
{
	actions_1.clear(); 
	actions_2.clear(); 

	return true;
}

void j1Cutscene::LoadData(pugi::xml_node& data, uint id) // Loads the cutscene selected. 
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
					iterator.speed = xml_actions.attribute("speed").as_uint();
					iterator.time = xml_actions.attribute("time").as_uint();
					iterator.actor = xml_actions.attribute("actor").as_int(); 

					//One list for each actor.
					if(iterator.actor == 1)
						actions_1.push_back(iterator);
					if(iterator.actor == 2)
						actions_2.push_back(iterator);
			}
		}
	}
	all_loaded = true; 
}

void j1Cutscene::Destination(int x, int y, uint speed, iPoint &actor_pos, Action &actor) 
{
	if (x > actor_pos.x)
		actor_pos.x += speed;
	else if (x < actor_pos.x)
		actor_pos.x -= speed;
	
	if (y > actor_pos.y)
		actor_pos.y += speed;
	else if (y < actor_pos.y)
		actor_pos.y -= speed;
}

void j1Cutscene::DoAction(list<Action> &actions, Action &actor)
{ 
	if (!actions.empty()) // List of actions. 
	{
		LOG("%d", actor.time);

		if (actions.front().time == count_time) // Do not start an action before the previous had finished (works individually on each actor).
		{
			actor.x = actions.front().x;
			actor.y = actions.front().y;
			actor.speed = actions.front().speed;

			actions.pop_front();
		}
	}
}

