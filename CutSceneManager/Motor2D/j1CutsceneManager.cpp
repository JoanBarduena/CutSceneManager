#include "j1CutsceneManager.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
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
	for (list<Cutscene*>::iterator cutscene_ip = cutscene_list.begin(); cutscene_ip != cutscene_list.end(); ++cutscene_ip)
	{

	}
}