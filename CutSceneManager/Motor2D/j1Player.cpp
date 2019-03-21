#include "j1Player.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"

j1Player::j1Player(): j1Module()
{
	name.assign("player");
}

j1Player::~j1Player()
{
}

bool j1Player::Awake()
{	
	return true;
}

bool j1Player::Start()
{
	graphics = App->tex->Load("textures/character.png");
	graphics2 = App->tex->Load("textures/character2.png"); 


	position.x = -10;
	position.y = 600;

	position2.x = 600; 
	position2.y = 600; 
	
	return true;
}

bool j1Player::PreUpdate()
{
	return true;
}


bool j1Player::Update(float dt)
{
	return true;
}

bool j1Player::PostUpdate()
{
	App->render->Blit(graphics, position.x, position.y);
	App->render->Blit(graphics2, position2.x, position2.y); 

	return true;
}

bool j1Player::CleanUp()
{
	App->tex->UnLoad(graphics);

	return true;
}
