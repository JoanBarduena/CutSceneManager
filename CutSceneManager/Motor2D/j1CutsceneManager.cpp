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
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		LoadData(xml, 2); 		
	}

	if (cutting_scene)
	{
		DoAction();
	}

	if (next_action == false)
	{
		Destination(destination.x, destination.y, destination.speed); 
		CheckDestination(destination.x, destination.y, destination.speed); 
	}

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
					iterator.x = xml_actions.attribute("position_x").as_int();
					iterator.y = xml_actions.attribute("position_y").as_int();
					iterator.speed = xml_actions.attribute("speed").as_int();

					actions.push_back(iterator);

					LOG("iterator = %d", iterator.x); 
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
	else
		App->player->position.x == x; 

	if (y > App->player->position.y)
		App->player->position.y += speed;
	else if (y < App->player->position.y)
		App->player->position.y -= speed;
	else
		App->player->position.y == y; 
}

void j1Cutscene::CheckDestination(int x, int y, uint speed)
{
	if (x + speed >= App->player->position.x && x - speed <= App->player->position.x
		&& speed + y >= App->player->position.y && y - speed <= App->player->position.y)
		next_action = true;
}

void j1Cutscene::DoAction()
{
	if(!actions.empty())// List of actions.
	{
		if (next_action) // Do not start an action before the previous had finished.
		{
			next_action = false;

			destination.x = actions.front().x;
			destination.y = actions.front().y;
			destination.speed = actions.front().speed;
		
			LOG("destination = %d", destination.x);
			actions.pop_front(); 
			
			LOG("%d", actions.size());
		}	
	}
}

