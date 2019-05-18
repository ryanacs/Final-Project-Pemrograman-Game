#include "Demo.h"

Demo::Demo()
{
}


Demo::~Demo()
{
	if (Mix_Playing(sfx_channel) == 0) {
		Mix_FreeChunk(sound);
	}
	if (music != NULL) {
		Mix_FreeMusic(music);
	}
	Mix_CloseAudio();
}

void Demo::Init()
{
	BuildBackground();
	InitAudio();
 
	BuildPlayerSprite();
	BuildCrateSprite();
	BuildCrateSprite2();
	BuildCrateSprite3();
	BuildCrateSprite4();
	BuildCrateSprite5();
	BuildCrateSprite6();
	BuildCrateSprite7();
	BuildCrateSprite8();
	BuildCrateSprite9();
	BuildCrateSprite10();

	BuildCollect();

	BuildPower();

	BuildBatas();
}

void Demo::Update(float deltaTime)
{
	if (IsKeyDown("Quit")) {
		SDL_Quit();
		exit(0);
	}

	if (Mix_Playing(sfx_channel) == 0 && IsKeyDown("SFX")) {
		sfx_channel = Mix_PlayChannel(-1, sound, 0);
		if (sfx_channel == -1) {
			Err("Unable to play WAV file: " + string(Mix_GetError()));
		}
	}
		
	if (IsKeyDown("Restart")) {
		SDLK_r;
		//player
		xpos = 200;
		ypos = 275;

		//obstacle
		xpos2 = 600;
		xpos3 = 600;
		xpos4 = 900;
		xpos5 = 900;		
		xpos7 = 1200;
		xpos8 = 1200;
		xpos10 = 1500;
		xpos11 = 1500;
		xpos12 = 1800;
		xpos13 = 1800;

		//collectible
		xpos6 = 900;

		//power up
		xpos9 = 750;
	}

	UpdatePlayerSpriteAnim(deltaTime);
	ControlPlayerSprite(deltaTime);
}

void Demo::Render()
{
	//Setting Viewport
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	DrawBackground();

	DrawPlayerSprite();
	DrawCrateSprite();
	DrawCrateSprite2();
	DrawCrateSprite3();
	DrawCrateSprite4();
	DrawCrateSprite5();
	DrawCrateSprite6();
	DrawCrateSprite7();
	DrawCrateSprite8();
	DrawCrateSprite9();
	DrawCrateSprite10();

	DrawCollect();

	DrawPower();

	DrawBatas();

	DrawMati();
}

void Demo::InitAudio() {
	int flags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG;
	if (flags != Mix_Init(flags)) {
		Err("Unable to initialize mixer: " + string(Mix_GetError()));
	}

	int audio_rate = 22050; Uint16 audio_format = AUDIO_S16SYS; int audio_channels = 2; int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		Err("Unable to initialize audio: " + string(Mix_GetError()));
	}
			
	sound = Mix_LoadWAV("BGM.wav");
	if (sound == NULL) {
		Err("Unable to load WAV file: " + string(Mix_GetError()));
	}
}

void Demo::UpdatePlayerSpriteAnim(float deltaTime)
{
	// Update animation
	frame_dur += deltaTime;

	if (walk_anim && frame_dur > FRAME_DUR) {
		frame_dur = 0;
		if (frame_idx == NUM_FRAMES - 1) frame_idx = 0;  else frame_idx++;

		// Pass frameIndex to shader
		UseShader(this->program);
		glUniform1i(glGetUniformLocation(this->program, "frameIndex"), frame_idx);
	}
}

void Demo::ControlPlayerSprite(float deltaTime)
{
	walk_anim = true;
	oldxpos = xpos;
	oldypos = ypos;
	//xpos += 60 * 0.1f;
	xpos2 += -30 * 0.1f;
	xpos3 += -30 * 0.1f;
	xpos4 += -30 * 0.1f;
	xpos5 += -30 * 0.1f;
	xpos6 += -30 * 0.1f;
	xpos7 += -30 * 0.1f;
	xpos8 += -30 * 0.1f;
	xpos9 += -30 * 0.1f;
	xpos10 += -30 * 0.1f;
	xpos11 += -30 * 0.1f;
	xpos12 += -30 * 0.1f;
	xpos13 += -30 * 0.1f;

	if (xpos > 200) xpos += -10 * 0.1f;/*Batas character dalam window*/
	if (xpos2 < -50) xpos2 = 1450;
	if (xpos3 < -50) xpos3 = 1450;
	if (xpos4 < -50) xpos4 = 1450;
	if (xpos5 < -50) xpos5 = 1450;
	if (xpos7 < -50) xpos7 = 1450;
	if (xpos8 < -50) xpos8 = 1450;
	if (xpos10 < -50) xpos10 = 1450;
	if (xpos11 < -50) xpos11 = 1450;
	if (xpos12 < -50) xpos12 = 1450;
	if (xpos13 < -50) xpos13 = 1450;
	if (ypos > GetScreenHeight()) ypos = oldypos;

	/*if (IsKeyDown("Move Right")) {
		xpos += 200 * xVelocity;
		flip = 0;
		walk_anim = true;
	}

	if (IsKeyDown("Move Left")) {
		xpos -= 200 * xVelocity;
		flip = 1;
		walk_anim = true;
	}*/

	if (IsKeyDown("Jump")) {
		ypos += 2 * 0.1f;
		//xpos += 30 * 0.1f;
		//if (onGround) {
			yVelocity = -0.02f * deltaTime;
			//onGround = true;
		//}
	}

	if (IsKeyUp("Jump")) {
		ypos += -2 * 0.1f;
		//xpos += 30 * 0.1f;
		if (yVelocity < -2.0f) {
			yVelocity = -2.0f;
		}
	}

	yVelocity += gravity * deltaTime;
	ypos += deltaTime * yVelocity;

	if (ypos > yposGround) {
		ypos = yposGround;
		yVelocity = 0;
		onGround = true;
	}


	// check collision between bart and crate
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos2, ypos2, frame_width2, frame_height2)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos3, ypos3, frame_width3, frame_height3)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos4, ypos4, frame_width4, frame_height4)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos5, ypos5, frame_width5, frame_height5)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos7, ypos7, frame_width7, frame_height7)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos8, ypos8, frame_width8, frame_height8)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos10, ypos10, frame_width10, frame_height10)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos11, ypos11, frame_width11, frame_height11)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos12, ypos12, frame_width12, frame_height12)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos13, ypos13, frame_width13, frame_height13)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}

	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos14, ypos14, frame_width14, frame_height14)) {
		VAO = SDLK_STOP;
		VAO2 = SDLK_STOP;
		VAO3 = SDLK_STOP;
		VAO4 = SDLK_STOP;
		VAO5 = SDLK_STOP;
		VAO6 = SDLK_STOP;
		VAO7 = SDLK_STOP;
		VAO8 = SDLK_STOP;
		VAO9 = SDLK_STOP;
		VAO10 = SDLK_STOP;
		VAO11 = SDLK_STOP;
		VAO12 = SDLK_STOP;
		VAO13 = SDLK_STOP;
		VAO14 = SDLK_STOP;
		BuildMati();
	}

	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos6, ypos6, frame_width6, frame_height6)) {
		VAO6 = SDLK_STOP;		
	}

	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos9, ypos9, frame_width9, frame_height9)) {
		VAO9 = SDLK_STOP;
		xpos += 300;
	}

	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos1, ypos1, frame_width1, frame_height1)) {
		
	}
}

void Demo::BuildBackground()
{
	this->program1 = BuildShader("obs6.vert", "obs6.frag");
	UseShader(this->program1);

	// Load and create a texture 
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("background2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width1 = (float)width;
	frame_height1 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &EBO1);

	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program1, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos1 = (GetScreenHeight() - frame_height1) / 2;
	ypos1 = (GetScreenHeight() - frame_height1) / 2;
}

void Demo::DrawBackground() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Activate shader
	UseShader(this->program1);
	glUniform1i(glGetUniformLocation(this->program1, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos1, ypos1, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width1, frame_height1, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program1, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO1);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::DrawPlayerSprite() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 0);

	// set flip
	glUniform1i(glGetUniformLocation(this->program, "flip"), flip);
	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos, ypos, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width, frame_height, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);
}

void Demo::BuildPlayerSprite()
{
	this->program = BuildShader("playerSprite.vert", "playerSprite.frag");

	// Pass n to shader
	UseShader(this->program);
	glUniform1f(glGetUniformLocation(this->program, "n"), 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("char1.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = ((float)width) / NUM_FRAMES;
	frame_height = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos = 200;
	ypos = yposGround - 275;
	yposGround = 550;
	//ypos = yposGround;
	gravity = 0.002f;
	xVelocity = 0.1f;

	// Add input mapping
	// to offer input change flexibility you can save the input mapping configuration in a configuration file (non-hard code) !
	//InputMapping("Move Right", SDLK_RIGHT);
	//InputMapping("Move Left", SDLK_LEFT);
	//InputMapping("Move Right", SDLK_d);
	//InputMapping("Move Left", SDLK_a);
	InputMapping("Move Right", SDL_BUTTON_RIGHT);
	InputMapping("Move Left", SDL_BUTTON_LEFT);
	InputMapping("Move Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	InputMapping("Move Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	InputMapping("Quit", SDLK_ESCAPE);
	InputMapping("Jump", SDLK_SPACE);
	InputMapping("Jump", SDL_CONTROLLER_BUTTON_A);
	InputMapping("Restart", SDLK_r);
	InputMapping("SFX", SDLK_s);
}

void Demo::BuildCrateSprite()
{
	this->program2 = BuildShader("crateSprite.vert", "crateSprite.frag");
	UseShader(this->program2);

	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall1.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width2 = (float)width;
	frame_height2 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program2, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos2 = 600;
	ypos2 = (GetScreenHeight() - frame_height2);
}

void Demo::DrawCrateSprite() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Activate shader
	UseShader(this->program2);
	glUniform1i(glGetUniformLocation(this->program2, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos2, ypos2, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width2, frame_height2, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program2, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO2);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCrateSprite2()
{
	this->program3 = BuildShader("obs2.vert", "obs2.frag");
	UseShader(this->program3);

	// Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width3 = (float)width;
	frame_height3 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);

	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program3, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos3 = 600;
	ypos3 = (GetScreenHeight() - frame_height3) / 200;
}

void Demo::DrawCrateSprite2() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture3);
	// Activate shader
	UseShader(this->program3);
	glUniform1i(glGetUniformLocation(this->program3, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos3, ypos3, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width3, frame_height3, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program3, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO3);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCrateSprite3()
{
	this->program4 = BuildShader("obs3.vert", "obs3.frag");
	UseShader(this->program4);

	// Load and create a texture 
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall3.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width4 = (float)width;
	frame_height4 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);

	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program4, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos4 = 900;
	ypos4 = (GetScreenHeight() - frame_height4);
}

void Demo::DrawCrateSprite3() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture4);
	// Activate shader
	UseShader(this->program4);
	glUniform1i(glGetUniformLocation(this->program4, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos4, ypos4, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width4, frame_height4, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program4, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO4);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCrateSprite4()
{
	this->program5 = BuildShader("obs4.vert", "obs4.frag");
	UseShader(this->program5);

	// Load and create a texture 
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall4.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width5 = (float)width;
	frame_height5 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);

	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program5, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos5 = 900;
	ypos5 = (GetScreenHeight() - frame_height5) / 200;
}

void Demo::DrawCrateSprite4() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture5);
	// Activate shader
	UseShader(this->program5);
	glUniform1i(glGetUniformLocation(this->program5, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos5, ypos5, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width5, frame_height5, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program5, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO5);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCrateSprite5()
{
	this->program7 = BuildShader("obs6.vert", "obs6.frag");
	UseShader(this->program7);

	// Load and create a texture 
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall1.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width7 = (float)width;
	frame_height7 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);

	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program7, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos7 = 1200;
	ypos7 = (GetScreenHeight() - frame_height7);
}

void Demo::DrawCrateSprite5() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture7);
	// Activate shader
	UseShader(this->program7);
	glUniform1i(glGetUniformLocation(this->program7, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos7, ypos7, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width7, frame_height7, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program7, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO7);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCrateSprite6()
{
	this->program8 = BuildShader("obs7.vert", "obs7.frag");
	UseShader(this->program8);

	// Load and create a texture 
	glGenTextures(1, &texture8);
	glBindTexture(GL_TEXTURE_2D, texture8); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width8 = (float)width;
	frame_height8 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO8);
	glGenBuffers(1, &VBO8);
	glGenBuffers(1, &EBO8);

	glBindVertexArray(VAO8);

	glBindBuffer(GL_ARRAY_BUFFER, VBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program8, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos8 = 1200;
	ypos8 = (GetScreenHeight() - frame_height8) / 200;
}

void Demo::DrawCrateSprite6() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture8);
	// Activate shader
	UseShader(this->program8);
	glUniform1i(glGetUniformLocation(this->program8, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos8, ypos8, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width8, frame_height8, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program8, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO8);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCrateSprite7()
{
	this->program10 = BuildShader("obs6.vert", "obs6.frag");
	UseShader(this->program10);

	// Load and create a texture 
	glGenTextures(1, &texture10);
	glBindTexture(GL_TEXTURE_2D, texture10); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width10 = (float)width;
	frame_height10 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO10);
	glGenBuffers(1, &VBO10);
	glGenBuffers(1, &EBO10);

	glBindVertexArray(VAO10);

	glBindBuffer(GL_ARRAY_BUFFER, VBO10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO10);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program10, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos10 = 1500;
	ypos10 = (GetScreenHeight() - frame_height10);
}

void Demo::DrawCrateSprite7() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture10);
	// Activate shader
	UseShader(this->program10);
	glUniform1i(glGetUniformLocation(this->program10, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos10, ypos10, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width10, frame_height10, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program10, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO10);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCrateSprite8()
{
	this->program11 = BuildShader("obs6.vert", "obs6.frag");
	UseShader(this->program11);

	// Load and create a texture 
	glGenTextures(1, &texture11);
	glBindTexture(GL_TEXTURE_2D, texture11); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall1.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width11 = (float)width;
	frame_height11 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO11);
	glGenBuffers(1, &VBO11);
	glGenBuffers(1, &EBO11);

	glBindVertexArray(VAO11);

	glBindBuffer(GL_ARRAY_BUFFER, VBO11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO11);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program11, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos11 = 1500;
	ypos11 = (GetScreenHeight() - frame_height11) / 200;
}

void Demo::DrawCrateSprite8() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture11);
	// Activate shader
	UseShader(this->program11);
	glUniform1i(glGetUniformLocation(this->program11, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos11, ypos11, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width11, frame_height11, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program11, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO11);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCrateSprite9()
{
	this->program12 = BuildShader("obs6.vert", "obs6.frag");
	UseShader(this->program12);

	// Load and create a texture 
	glGenTextures(1, &texture12);
	glBindTexture(GL_TEXTURE_2D, texture12); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall3.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width12 = (float)width;
	frame_height12 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO12);
	glGenBuffers(1, &VBO12);
	glGenBuffers(1, &EBO12);

	glBindVertexArray(VAO12);

	glBindBuffer(GL_ARRAY_BUFFER, VBO12);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO12);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program12, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos12 = 1800;
	ypos12 = (GetScreenHeight() - frame_height12);
}

void Demo::DrawCrateSprite9() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture12);
	// Activate shader
	UseShader(this->program12);
	glUniform1i(glGetUniformLocation(this->program12, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos12, ypos12, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width12, frame_height12, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program12, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO12);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCrateSprite10()
{
	this->program13 = BuildShader("obs6.vert", "obs6.frag");
	UseShader(this->program13);

	// Load and create a texture 
	glGenTextures(1, &texture13);
	glBindTexture(GL_TEXTURE_2D, texture13); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall4.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width13 = (float)width;
	frame_height13 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO13);
	glGenBuffers(1, &VBO13);
	glGenBuffers(1, &EBO13);

	glBindVertexArray(VAO13);

	glBindBuffer(GL_ARRAY_BUFFER, VBO13);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO13);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program13, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos13 = 1800;
	ypos13 = (GetScreenHeight() - frame_height13) / 200;
}

void Demo::DrawCrateSprite10() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture13);
	// Activate shader
	UseShader(this->program13);
	glUniform1i(glGetUniformLocation(this->program13, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos13, ypos13, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width13, frame_height13, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program13, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO13);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildBatas()
{
	this->program14 = BuildShader("obs6.vert", "obs6.frag");
	UseShader(this->program14);

	// Load and create a texture 
	glGenTextures(1, &texture14);
	glBindTexture(GL_TEXTURE_2D, texture14); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("wall5.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width14 = (float)width;
	frame_height14 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO14);
	glGenBuffers(1, &VBO14);
	glGenBuffers(1, &EBO14);

	glBindVertexArray(VAO14);

	glBindBuffer(GL_ARRAY_BUFFER, VBO14);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO14);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program14, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos14 = 300;
	ypos14 = 599;
}

void Demo::DrawBatas() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture14);
	// Activate shader
	UseShader(this->program14);
	glUniform1i(glGetUniformLocation(this->program14, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos14, ypos14, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width14, frame_height14, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program14, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO14);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildCollect()
{
	this->program6 = BuildShader("obs5.vert", "obs5.frag");
	UseShader(this->program6);

	// Load and create a texture 
	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("collect.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width6 = (float)width;
	frame_height6 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);

	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program6, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos6 = 900;
	ypos6 = (GetScreenHeight() - frame_height6) / 2;
}

void Demo::DrawCollect() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture6);
	// Activate shader
	UseShader(this->program6);
	glUniform1i(glGetUniformLocation(this->program6, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos6, ypos6, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width6, frame_height6, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program6, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO6);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildPower()
{
	this->program9 = BuildShader("obs8.vert", "obs8.frag");
	UseShader(this->program9);

	// Load and create a texture 
	glGenTextures(1, &texture9);
	glBindTexture(GL_TEXTURE_2D, texture9); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("bolt.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width9 = (float)width;
	frame_height9 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO9);
	glGenBuffers(1, &VBO9);
	glGenBuffers(1, &EBO9);

	glBindVertexArray(VAO9);

	glBindBuffer(GL_ARRAY_BUFFER, VBO9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO9);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program9, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos9 = 750;
	ypos9 = (GetScreenHeight() - frame_height9) / 6;
}

void Demo::DrawPower() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture9);
	// Activate shader
	UseShader(this->program9);
	glUniform1i(glGetUniformLocation(this->program9, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos9, ypos9, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width9, frame_height9, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program9, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO9);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Demo::BuildMati()
{
	this->program15 = BuildShader("obs6.vert", "obs6.frag");
	UseShader(this->program15);

	// Load and create a texture 
	glGenTextures(1, &texture15);
	glBindTexture(GL_TEXTURE_2D, texture15); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("mati.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width15 = (float)width;
	frame_height15 = (float)height;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO15);
	glGenBuffers(1, &VBO15);
	glGenBuffers(1, &EBO15);

	glBindVertexArray(VAO15);

	glBindBuffer(GL_ARRAY_BUFFER, VBO15);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO15);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program15, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos15 = (GetScreenWidth() - frame_width15) / 2;
	ypos15 = (GetScreenHeight() - frame_height15) / 2;
}

void Demo::DrawMati() {
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture15);
	// Activate shader
	UseShader(this->program15);
	glUniform1i(glGetUniformLocation(this->program15, "ourTexture"), 1);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos15, ypos15, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width15, frame_height15, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program15, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO15);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

bool Demo::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}


int main(int argc, char** argv) {

	Engine::Game &game = Demo();
	game.Start(/*"Collision Detection using AABB"*/"Runaway", 800, 600, false, WindowFlag::WINDOWED, 60, 1);

	return 0;
}
