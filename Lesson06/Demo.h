#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

#define NUM_FRAMES 8
#define FRAME_DUR 80

using namespace glm;

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void InitAudio();
	float frame_width1 = 0, frame_height1 = 0, frame_width = 0, frame_height = 0, frame_width2 = 0, frame_height2 = 0, frame_width3 = 0, frame_height3 = 0,
		frame_width4 = 0, frame_height4 = 0, frame_width5 = 0, frame_height5 = 0, frame_width6 = 0, frame_height6 = 0,
		frame_width7 = 0, frame_height7 = 0, frame_width8 = 0, frame_height8 = 0, frame_width9 = 0, frame_height9 = 0, 
		frame_width10 = 0, frame_height10 = 0, frame_width11 = 0, frame_height11 = 0, frame_width12 = 0, frame_height12 = 0,
		frame_width13 = 0, frame_height13 = 0, frame_width14 = 0, frame_height14 = 0, frame_width15 = 0, frame_height15 = 0;
private:
	Mix_Chunk *sound = NULL;
	Mix_Music *music = NULL;
	int sfx_channel = -1;
	float xpos1 = 0, ypos1 = 0, frame_dur = 0, oldxpos = 0, oldypos = 0, xpos = 0, ypos = 0, xpos2 = 0, ypos2 = 0, xpos3 = 0, ypos3 = 0,
		xpos4 = 0, ypos4 = 0, xpos5 = 0, ypos5 = 0, xpos6 = 0, ypos6 = 0, xpos7 = 0, ypos7 = 0, xpos8 = 0, ypos8 = 0,
		xpos9 = 0, ypos9 = 0, xpos10 = 0, ypos10 = 0, xpos11 = 0, ypos11 = 0, xpos12 = 0, ypos12 = 0, xpos13 = 0, ypos13 = 0, xpos14 = 0, ypos14 = 0,
		xpos15 = 0, ypos15 = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;
	GLuint VBO1, VAO1, EBO1, texture1, program1, VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2, VBO3, VAO3, EBO3, texture3, program3,
		VBO4, VAO4, EBO4, texture4, program4, VBO5, VAO5, EBO5, texture5, program5, VBO6, VAO6, EBO6, texture6, program6,
		VBO7, VAO7, EBO7, texture7, program7, VBO8, VAO8, EBO8, texture8, program8, VBO9, VAO9, EBO9, texture9, program9,
		VBO10, VAO10, EBO10, texture10, program10, VBO11, VAO11, EBO11, texture11, program11, VBO12, VAO12, EBO12, texture12,
		program12, VBO13, VAO13, EBO13, texture13, program13, VBO14, VAO14, EBO14, texture14, program14, VBO15, VAO15, EBO15, texture15, program15;
	bool walk_anim = false, onGround = true;
	unsigned int frame_idx = 0, flip = 0;
	void BuildBackground();
	void DrawBackground();

	void BuildPlayerSprite();

	void BuildCrateSprite();
	void DrawCrateSprite();
	void BuildCrateSprite2();
	void DrawCrateSprite2();
	void BuildCrateSprite3();
	void DrawCrateSprite3();
	void BuildCrateSprite4();
	void DrawCrateSprite4();
	void BuildCrateSprite5();
	void DrawCrateSprite5();
	void BuildCrateSprite6();
	void DrawCrateSprite6();
	void BuildCrateSprite7();
	void DrawCrateSprite7();
	void BuildCrateSprite8();
	void DrawCrateSprite8();
	void BuildCrateSprite9();
	void DrawCrateSprite9();
	void BuildCrateSprite10();
	void DrawCrateSprite10();

	void BuildCollect();
	void DrawCollect();

	void BuildPower();
	void DrawPower();
	
	void BuildBatas();
	void DrawBatas();

	void BuildMati();
	void DrawMati();

	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);

	void DrawPlayerSprite();
	void UpdatePlayerSpriteAnim(float deltaTime);
	void ControlPlayerSprite(float deltaTime);
};
#endif

