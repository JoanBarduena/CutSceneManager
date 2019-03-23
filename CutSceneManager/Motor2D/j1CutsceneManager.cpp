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
		DoAction();
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		LoadData(xml, 2); 
		DoAction();
	}

	

	return true;
}

bool j1Cutscene::PostUpdate()
{
	/*CheckDestination(actor_x, actor1_y); */

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
					iterator.actor_x = xml_actions.attribute("position_x").as_int();
					iterator.actor_y = xml_actions.attribute("position_y").as_int();
					iterator.actor_speed = xml_actions.attribute("speed").as_int();

					actions.push_back(&iterator);
			}
		}
	}

	cutting_scene = true;
}

void j1Cutscene::Destination(int x, int y, uint speed)
{
	LOG("%d", x); 
	LOG("%d", App->player->position.x); 

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
	if (x == App->player->position.x && y == App->player->position.y)
		doing_cut = false;
}

void j1Cutscene::DoAction()
{
	for (list<Action*>::iterator iterator = actions.begin(); iterator != actions.end(); iterator++)
	{
		App->player->position.x = (*iterator)->actor_x;
		App->player->position.y = (*iterator)->actor_y;
	}
}

