#include "j1Player.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1CutsceneManager.h"

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


	position.x = -400;
	position.y = 700;

	position2.x = 600; 
	position2.y = 400; 
	
	return true;
}

bool j1Player::PreUpdate()
{
	return true;
}


bool j1Player::Update(float dt)
{
	if (!App->cutscene->all_loaded)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			position.y -= 2;
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			position.x -= 2;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			position.y += 2;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			position.x += 2;

		if (position.x >= 500)
			position.x = 500;
		if (position.y >= 1020)
			position.y = 1020;
		if (position.x <= -475)
			position.x = -475;
		if (position.y <= 300)
			position.y = 300;
	}

	LOG("pos.x %d", position.x);
	LOG("pos.y %d", position.y); 



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
	App->tex->UnLoad(graphics2); 

	return true;
}
