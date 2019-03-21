#ifndef __j1Cutscene_H__
#define __j1Cutscene_H__

#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

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

	void LoadData(std::string scene, )

};

#endif // __j1Cutscene_H__
