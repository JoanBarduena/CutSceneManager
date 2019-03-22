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
		doing_cut = true;  
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		LoadData(xml, 2); 
		doing_cut = true; 
	}

	return true;
}

bool j1Cutscene::PostUpdate()
{
	if (doing_cut)
		Destination(actor1_x, actor1_y, actor1_speed);

	CheckDestination(actor1_x, actor1_y); 

	return true;
}

bool j1Cutscene::CleanUp()
{
	return true;
}

void j1Cutscene::LoadData(pugi::xml_node& data, uint id)
{
	pugi::xml_node cutscene_id; 

	for (cutscene_id = data.child("cutscene"); cutscene_id; cutscene_id = cutscene_id.next_sibling("cutscene"))
	{
		if (cutscene_id.attribute("id").as_uint() == id)
		{
			actor1_x = cutscene_id.child("actor_1").attribute("position_x").as_int(); 
			actor1_y = cutscene_id.child("actor_1").attribute("position_y").as_int(); 
			actor1_speed = cutscene_id.child("actor_1").attribute("speed").as_int();

			dest_x = actor1_x; //Saving position X of the destination. 
			dest_y = actor1_y; //Saving position Y of the destination. 
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

void j1Cutscene::CheckDestination(int x, int y)
{
	if (x == dest_x && y == dest_y)
		doing_cut = false;
}