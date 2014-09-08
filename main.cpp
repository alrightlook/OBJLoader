#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>
#include "obj3dmodel.h"

using namespace std;
SDL_GLContext g_glContext;
void InitGL()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetSwapInterval(1);
}
void SetPerspective(double x = 0.0, double y =50.0, double z = -150.0)
{
	glClearColor(0.5f,0.5f,0.5f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 1.0f, 1000.0f);
	gluLookAt(x,y,z, 0.0,50.0,0.0, 0.0,1.0,0.0);
}
void Draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);

		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
	glFlush();
}
int main(int argc, char* argv[])
{
	double posx = 0.0;
	double posy = 50.0;
	double posz = -150.0;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		cout<<"SDL init Error:"<<SDL_GetError()<<endl;
	}
	InitGL();
	SDL_Window* win = 0;
	win = SDL_CreateWindow ("Hello SDL", 100,100,1024,768, SDL_WINDOW_OPENGL);
	g_glContext = SDL_GL_CreateContext(win);
/*	SDL_Renderer* ren = 0;
	ren = SDL_CreateRenderer (win, -1, SDL_RENDERER_ACCELERATED);
	*/
	bool quit = false;
	SetPerspective();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	obj3dmodel model;
	model.Parse("./monster.obj");
	model.Rotate(180.0, 0.0, 1.0, 0.0);
	while(!quit)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if( e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				if(e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}
				if(e.key.keysym.sym == SDLK_r) {
					glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
					model.Rotate(5, 0.0,1.0,0.0);
				}
				else if( e.key.keysym.sym == SDLK_w) {
					posz += 5;
					SetPerspective(posx, posy, posz);
				}
				else if( e.key.keysym.sym == SDLK_s) {
					posz -= 5;
					SetPerspective(posx, posy, posz);
				}
			}
	//		SDL_RenderClear(ren);
	//		SDL_RenderPresent(ren);
		}
			glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
			model.Draw();
			SDL_GL_SwapWindow(win);
	}
	SDL_Quit();
	return 0;
}
