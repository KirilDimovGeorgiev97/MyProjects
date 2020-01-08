

#include <GL\glew.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <gl\GLU.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include "GeometryNode.h"
#include "GroupNode.h"
#include "TransformNode.h"


bool init();
bool initGL();
void render();
GLuint CreateCube(float, GLuint&, GLuint&);
void DrawCube(GLuint id);
void close();


void CreateScene();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

Shader gShader;
Model gModel;
Model gModel2;

GroupNode* gRoot;
TransformNode* trSuit2 = new TransformNode("Nanosuit Transform2");
TransformNode* trWindsurf = new TransformNode("windsurf");

float x = -38.0f;
float ya = 0.0;
float yb = 0.0;
float yb2 = 0.0f;
float i = 0.0f;

float r = 0.0;
float z = 0.0;
float t = 0.0;
bool flag1 = false;
bool flag2 = false;




GLuint gVAO, gVBO, gEBO;

// camera
Camera camera(glm::vec3(0.0f, 2.0f, 3.0f));
float lastX = -1;
float lastY = -1;
bool firstMouse = true;

// timing
float deltaTime = 20.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//statics
unsigned int Node::genID;
glm::mat4 TransformNode::transformMatrix = glm::mat4(1.0f);

//event handlers
void HandleKeyDown(const SDL_KeyboardEvent& key);
void HandleMouseMotion(const SDL_MouseMotionEvent& motion);
void HandleMouseWheel(const SDL_MouseWheelEvent& wheel);
void HandleKeyUp(const SDL_KeyboardEvent& key);
SDL_KeyboardEvent key;

void move();
void rotate();
void rotate2();
void rotate21();

int main(int argc, char* args[])
{
	init();

	CreateScene();

	SDL_Event e;
	//While application is running
	bool quit = false;
	while (!quit)
	{
		// per-frame time logic
		// --------------------
		float currentFrame = SDL_GetTicks() / 1000.0f;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
				else
				{
					HandleKeyDown(e.key);
					HandleKeyUp(e.key);
				}
				break;
			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
				else {
					printf("vutre ");
					HandleKeyUp(e.key);
				}
				break;
			case SDL_MOUSEMOTION:
				HandleMouseMotion(e.motion);
				break;
			case SDL_MOUSEWHEEL:
				HandleMouseWheel(e.wheel);
				break;
			}
		}

		//Render
		render();
		//move();

		//Update screen
		SDL_GL_SwapWindow(gWindow);
	}

	close();

	return 0;
}

void HandleKeyDown(const SDL_KeyboardEvent& key)
{
	switch (key.keysym.sym)
	{
	case SDLK_w:
		camera.ProcessKeyboard(FORWARD, deltaTime);
		break;
	case SDLK_s:
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		break;
	case SDLK_a:
		camera.ProcessKeyboard(LEFT, deltaTime);
		break;
	case SDLK_d:
		camera.ProcessKeyboard(RIGHT, deltaTime);
		break;
	}
}


void HandleKeyUp(const SDL_KeyboardEvent& key)
{
	if (key.type == SDL_KEYDOWN && key.keysym.scancode == 58/*F1*/) {
		printf("\n %lf -yb", yb);
		yb -= 0.1;
		move();
	}
	else if (key.type == SDL_KEYDOWN && key.keysym.scancode == 59/*F2*/ && flag1==false) {
		yb -= 0.1f;
		r += 0.3f;
		rotate();
		
		if(yb<-29.0f)
			ya += 0.15f;

		if (r >= 180.0f)
			flag1 = true;
		
		printf("\n %f r and %f yb", r, yb);
		if (r >= 88.0f)
			rotate2();
		else
			ya -= 0.15f;
	}
	else if (key.type == SDL_KEYDOWN && key.keysym.scancode == 60) {
		printf("\n %lf", yb);
		yb += 0.1;
		move();
	}
	else if (key.type == SDL_KEYDOWN && key.keysym.scancode == 61/*F4*/ && flag1 == true) {
		yb += 0.1f;
		r -= 0.3f;
		rotate();

		if(yb>=-29.0f)
			ya += 0.15f;
		else
			ya -= 0.15f;

		if (r <= 0.0f)
			flag1 = false;

		printf("\n %f r and %f yb   %f ya   F4", r, yb, ya);
		if (r <= 88.0f)
			rotate21();
		


	}
}

void HandleMouseMotion(const SDL_MouseMotionEvent& motion)
{
	if (firstMouse)
	{
		lastX = motion.x;
		lastY = motion.y;
		firstMouse = false;
	}
	else
	{
		camera.ProcessMouseMovement(motion.x - lastX, lastY - motion.y);
		lastX = motion.x;
		lastY = motion.y;
	}
}

void HandleMouseWheel(const SDL_MouseWheelEvent& wheel)
{
	camera.ProcessMouseScroll(wheel.y);
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use OpenGL 3.3
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	glewInit();

	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
	}

	glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gShader.Load("./shaders/vertex.vert", "./shaders/fragment.frag");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //other modes GL_FILL, GL_POINT

	return success;
}

void CreateScene()
{
	gRoot = new GroupNode("root");

/*	TransformNode* trSuit = new TransformNode("Nanosuit Transform");
	trSuit->SetTranslation(glm::vec3(3.0f, 0.0f, 1.0f));
	trSuit->SetScale(glm::vec3(0.01f, 0.01f, 0.01f));
	GeometryNode *nanosuit = new GeometryNode("nanosuit");
	nanosuit->LoadFromFile("models/nanosuit/nanosuit.obj");
	nanosuit->SetShader(&gShader);
	trSuit->AddChild(nanosuit);
	gRoot->AddChild(trSuit);

	TransformNode* tr2 = new TransformNode("Nanosuit Transform 2");
	trSuit->SetTranslation(glm::vec3(2.0f, 0.0f, 1.0f));
	trSuit->SetScale(glm::vec3(0.01f, 0.01f, 0.01f));
	//tr2->SetTranslation(glm::vec3(-2.0f, -1.0f, 0.0f));
	GeometryNode *nanosuit2 = new GeometryNode("nanosuit2");
	nanosuit2->LoadFromFile("models/nanosuit/nanosuit3.obj");
	nanosuit2->SetShader(&gShader);
	tr2->AddChild(nanosuit2);
	trSuit->AddChild(tr2);

	TransformNode* tr3 = new TransformNode("Nanosuit Transform 3");
	trSuit->SetTranslation(glm::vec3(2.0f, 0.0f, 1.0f));
	trSuit->SetScale(glm::vec3(0.01f, 0.01f, 0.01f));
	//tr2->SetTranslation(glm::vec3(-2.0f, -1.0f, 0.0f));
	GeometryNode *nanosuit3 = new GeometryNode("nanosuit3");
	nanosuit3->LoadFromFile("models/nanosuit/nanosuit3.obj");
	nanosuit3->SetShader(&gShader);
	//tr2->AddChild(nanosuit2);
	//trSuit->AddChild(tr2);*/

//	TransformNode* trSuit = new TransformNode("Nanosuit Transform");
//	trSuit->SetTranslation(glm::vec3(0.0f, 0.0f, 1.0f));
//	trSuit->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	//trSuit->SetRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
/*	glm::mat4 transform1 = TransformNode::GetTransformMatrix();
	transform1 = glm::rotate(transform1, -91.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	trSuit->SetTransformMatrix(transform1);*/

	/*GeometryNode *nanosuit = new GeometryNode("nanosuit");
	nanosuit->LoadFromFile("models/nanosuit/nanosuit.obj");
	nanosuit->SetShader(&gShader);
	trSuit->AddChild(nanosuit);
	gRoot->AddChild(trSuit);*/


	//TransformNode* trWindsurf = new TransformNode("windsurf");
	trWindsurf->SetTranslation(glm::vec3(4.0f, 0.0f, 1.0f));
	trWindsurf->SetScale(glm::vec3(0.01f, 0.01f, 0.01f));
	trWindsurf->SetRotation(-90.0f, 0.0f, 0.0f );


	GeometryNode *windsurf = new GeometryNode("windsurf");
	windsurf->LoadFromFile("models/nanosuit/windsurf.obj");
	windsurf->SetShader(&gShader);
	trWindsurf->AddChild(windsurf);
	gRoot->AddChild(trWindsurf);


	//TransformNode* trSuit2 = new TransformNode("Nanosuit Transform2");
	trSuit2->SetTranslation(glm::vec3(x, 0.0f, 10.0f));
	trSuit2->SetScale(glm::vec3(10.0f, 10.0f, 10.0f));
	trSuit2->SetRotation(90.0f, 90.0f, 0.0f);
	//trSuit2->SetRotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//trSuit2->SetRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//trSuit2->SetRotation(-270.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//trSuit2->SetRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//trSuit2->SetRotation(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	//trSuit2->SetRotation(150.0f, glm::vec3(1.0f, 0.0f, 0.0f));


	GeometryNode *nanosuit2 = new GeometryNode("nanosuit2");
	nanosuit2->LoadFromFile("models/nanosuit/nanosuit2.obj");
	nanosuit2->SetShader(&gShader);
	trSuit2->AddChild(nanosuit2);
	trWindsurf->AddChild(trSuit2);



	/*trWindsurf->SetTranslation(glm::vec3(10.0f, 0.0f, 1.0f));
	trWindsurf->SetScale(glm::vec3(0.01f, 0.01f, 0.01f));
	trWindsurf->SetRotation(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	/*glm::mat4 transform = TransformNode::GetTransformMatrix();
	transform = glm::rotate(transform, 100.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	trWindsurf->SetTransformMatrix(transform);*/

	/*GeometryNode *windsurf = new GeometryNode("windsurf");
	windsurf->LoadFromFile("models/nanosuit/windsurf.obj");
	windsurf->SetShader(&gShader);
	trWindsurf->AddChild(windsurf);
	gRoot->AddChild(trWindsurf);*/






}

void close()
{
	//delete GL programs, buffers and objects
	glDeleteProgram(gShader.ID);
	glDeleteVertexArrays(1, &gVAO);
	glDeleteBuffers(1, &gVBO);

	//Delete OGL context
	SDL_GL_DeleteContext(gContext);
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

/*void render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 model = glm::mat4(1.0f);
//	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
	//depending on the model size, the model may have to be scaled up or down to be visible
//  model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
//	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat3 normalMat = glm::transpose(glm::inverse(model));

	glUseProgram(gShader.ID);
	gShader.setMat4("model", model);
	gShader.setMat4("view", view);
	gShader.setMat4("proj", proj);
	gShader.setMat3("normalMat", normalMat);

	//lighting
	gShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	gShader.setVec3("light.position", lightPos);
	gShader.setVec3("viewPos", camera.Position);

	gModel.Draw(gShader);

	model = glm::scale(glm::mat4(1.0), glm::vec3(0.02, 0.02, 0.02));
	gShader.setMat4("model", model);
	gModel2.Draw(gShader);

//	DrawCube(gVAO);
}*/

void move() {

	trWindsurf->SetTranslation(glm::vec3(-2.0f, 0.0, 0.0f+yb));
}

void rotate() {
	trWindsurf->SetTranslation(glm::vec3(-2.0f, 0.0f, 0.0f + yb));
	trWindsurf->SetRotation(-90.0f, 0.0f , 0.0f + r);
	trSuit2->SetTranslation(glm::vec3(x, 0.0f-ya, 10.0f));
}

void rotate2() { //108.75
	trSuit2->SetRotation(90.0f, 0.0f, 0.0f);
	x = 38.0f;
	trSuit2->SetTranslation(glm::vec3(x, 0.0f - ya, 10.0f));
	trSuit2->SetRotation(90.0f, -90.0f, 0.0f);
}

void rotate21() { //108.75
	trSuit2->SetRotation(90.0f, 0.0f, 0.0f);
	x = -38.0f;
	trSuit2->SetTranslation(glm::vec3(x, 0.0f - ya, 10.0f));
	trSuit2->SetRotation(90.0f, 90.0f, 0.0f);
}


void render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), 4.0f / 3.0f, 0.1f, 100.0f);
	//trWindsurf->SetTranslation(glm::vec3(-2.0f, 0.0, yb));
	//trWindsurf->SetRotation(z, glm::vec3(0.0f, 1.0f, 0.0f));

	

	glUseProgram(gShader.ID);
	gShader.setMat4("view", view);
	gShader.setMat4("proj", proj);

	//lighting
	gShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	gShader.setVec3("light.position", lightPos);
	gShader.setVec3("viewPos", camera.Position);

	gRoot->Traverse();
	
}

GLuint CreateCube(float width, GLuint& VBO)
{
	//each side of the cube with its own vertices to use different normals
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	GLuint VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //the data comes from the currently bound GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	return VAO;
}

void DrawCube(GLuint vaoID)
{
	glBindVertexArray(vaoID);
	//glDrawElements uses the indices in the EBO to get to the vertices in the VBO
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}


