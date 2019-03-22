#include "j1CutsceneManager.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Player.h"
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
		Destination(actor1_x, actor1_y); 
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
	App->

	pugi::xml_node cutscene_id; 

	for (cutscene_id = data.child("cutscene"); cutscene_id; cutscene_id = cutscene_id.next_sibling("cutscene"))
	{
		if (cutscene_id.attribute("id").as_uint() == id)
		{
			actor1_x = cutscene_id.child("actor_1").attribute("position_x").as_int(); 
			actor1_y = cutscene_id.child("actor_1").attribute("position_y").as_int(); 
			actor1_speed = cutscene_id.child("actor_1").attribute("speed").as_int();
		}
	}

	cutting_scene = true;
}

void j1Cutscene::Destination(int x, int y)
{
	App->player->position.x = x; 
	App->player->position.y = y; 
}