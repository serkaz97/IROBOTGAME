// IROBOTGAME.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <mmsystem.h>
using namespace std;
//Function Section
//***********************************************
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);
void OnMouseMove(int, int);
void LoadObjects();
void LoadColliders();
void checkCollisions();
void gainPoint();
void OpenDoorsCheck();
void SquareCollider(vec3 p, float r);
void trashGen(float x_min, float x_max, float y_min, float y_max);
float min(float x, float y);
float max(float x, float y);
float T = 0;
int tbef = 0;
//***********************************************

//Variable Section
//***********************************************
int window_width, window_height;
bool captureMouse;
bool keystate[256];
bool unlock=false;
int flag = 0;
bool room1=false, room2=false, room3=false;
//***********************************************

//Object Section
//***********************************************
Player *player;
Scene  scene;
vec3 mousePosition;
Obj3d *Home;
Collider *Col1, *Col2;
clock_t start;
//***********************************************
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("IROBOT SIM");

	//***************************
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);
	glutPassiveMotionFunc(OnMouseMove);
	glClearColor(0.1f, 0.2f, 0.3f, 0.0);
	//*****************************
	glEnable(GL_DEPTH_TEST);

	//*****************************

	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glutSetCursor(GLUT_CURSOR_NONE);
	captureMouse = true;
	glutWarpPointer(window_width / 2, window_height / 2);

	LoadObjects();
	LoadColliders();
	PlaySound(TEXT("../Resources/Sounds/sound2.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	start = clock();

	glutMainLoop();
    return 0;
}

void OnRender()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, -1, -2);
	float previousT = T;
	T = glutGet(GLUT_ELAPSED_TIME);
	clock_t pom = clock();
	int t=(int)(double(pom - start) / 1000);
	if (t!=tbef)
	{
		tbef = t;
		if (t % 5 == 0)
		{
			scene.hud.energy--;
			start = clock();
		}
	}
	scene.hud.fps = 1.0f / (T - previousT) * 1000;
	scene.guiDisplay();
	gluLookAt(
		player->pos.x, player->pos.y, player->pos.z,
		player->pos.x + player->dir.x, player->pos.y + player->dir.y, player->pos.z + player->dir.z,
		0.0f, 1.0f, 0.0f);

	{
		GLfloat l0_ambient[] = { 0.2f, 0.2f, 0.2f };
		GLfloat l0_diffuse[] = { 1.0f, 1.0f, 1.0 };
		GLfloat l0_specular[] = { 0.5f, 0.5f, 0.5f };
		GLfloat l0_position[] = { -5.6, 0.5,-2., 1.0f };

		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_position);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	}
	
	{
		GLfloat l0_ambient[] = { 0.0f, 0.0f, 0.0f };
		GLfloat l0_diffuse[] = { 0.5f, 0.5f, 0.5 };
		GLfloat l0_specular[] = { 0.2f, 0.2f, 0.2f };
		GLfloat l0_position[] = { -player->dir.x, player->dir.y, -player->dir.z, 0.0f };

		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, l0_position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);

	}
	{
		GLfloat l0_ambient[] = { 0.2f, 0.2f, 0.2f };
		GLfloat l0_diffuse[] = { 1.0f, 1.0f, 1.0 };
		GLfloat l0_specular[] = { 0.5f, 0.5f, 0.5f };
		GLfloat l0_position[] = { 20, 3,-2., 1.0f };

		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT2, GL_POSITION, l0_position);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);
	}
	{
		GLfloat l0_ambient[] = { 0.2f, 0.2f, 0.2f };
		GLfloat l0_diffuse[] = { 1.0f, 1.0f, 1.0 };
		GLfloat l0_specular[] = { 0.5f, 0.5f, 0.5f };
		GLfloat l0_position[] = { -5.6, 3,-2., 1.0f };

		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT3, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT3, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT3, GL_POSITION, l0_position);
		glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0);
	}
	
	//OpenDoorsCheck();
	scene.Render();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

};

void OnReshape(int width, int height) {

	window_width = width;
	window_height = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)width / height, .01f, 100.0f);
}
void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		OnKeyDown(key, x, y);
	}
	keystate[key] = true;
}

void OnKeyDown(unsigned char key, int x, int y) {
	if (key == 27) {
		glutLeaveMainLoop();
	}
	if (key == 'f')
	{
		player->flyingMode = !player->flyingMode;
	}
	if (key == 'p')
	{
		cout << "x: " << player->pos.x << " y: " << player->pos.y << " z: " << player->pos.z << endl;
	}
	if (key == 'q')
	{
		player->collide = !player->collide;
	}
	if (key == 'm')
	{
		if (captureMouse)
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			captureMouse = false;
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(window_width / 2, window_height / 2);
			captureMouse = true;
		}
	}
	if (key == '-')
	{
		player->speed -= 0.01;
	}
	if (key == '+')
	{
		player->speed += 0.01;
	}

}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void OnMouseMove(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}

void OnTimer(int id) {
	if (scene.hud.energy == 0)
	{
		player->speed = 0;
		
	}
	if (player->points == 1600 && room1 == false)
	{	
			trashGen(6.7, 12.2, -10.4, 5.2);
			room1 = true;
			scene.doors[0]->open = true;
			scene.colliders.pop_back();
	}
	if (player->points == 3600 && room2 == false)
	{
			trashGen(13.5, 21.2, -16.9, -2.5);
			room2 = true;
			scene.doors[1]->open = true;
			scene.colliders.pop_back();
	}
	if (player->points == 4600 && room3 == false)
	{
		trashGen(13., 21.2, -1.6, 5.1);
		room3 = true;
		scene.doors[2]->open = true;
		scene.colliders.pop_back();
	}



	if (keystate['w']) {
		player->velocity_vertical = 1;
	}
	if (keystate['s']) {
		player->velocity_vertical = -1;
	}
	if (keystate['a']) {
		player->velocity_horizontal = 1;
	}
	if (keystate['d']) {
		player->velocity_horizontal = -1;
	}

	if (captureMouse)
	{
		float theta = atan2(player->dir.z, player->dir.x);
		float phi = asin(player->dir.y);

		theta += (mousePosition.x - window_width / 2) * 0.01;
		phi -= (mousePosition.y - window_height / 2) * 0.01;

		player->dir.x = cos(theta) * cos(phi);
		if (sin(phi) <= 0.4 &&  sin(phi) >= -0.25)
			player->dir.y = sin(phi);
		else if (sin(phi) > 0.4)
			player->dir.y = 0.4;	
		else if (sin(phi) < -.25)
			player->dir.y = -.25;
		player->dir.z = sin(theta) * cos(phi);

		glutWarpPointer(window_width / 2, window_height / 2);
	}
	checkCollisions();
	gainPoint();
	scene.Update();
	glutTimerFunc(17, OnTimer, 0);
}
//static float i, j, k;

void LoadObjects()
{
	//Player
	player = new Player();
	scene.AddObject(player);

	//Mieszkanie
	Home = new Obj3d(vec3(0, -2, 0), vec3(1, 1, 1), 0.f, 1.f);
	Home->load("../Resources/Models/home2.obj");
	Home->textureName = "home";
	scene.AddObject(Home);
	TextureManager::getInstance()->LoadTexture("home", "../Resources/Textures/home.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	//Futryny
	Obj3d* Futryna;
	Futryna = new Obj3d(vec3(6.25, 0.01, -4), vec3(1, 1, 1), 0.f, 1.f);
	Futryna->load("../Resources/Models/futryna.obj");
	Futryna->textureName = "futryna";
	scene.AddObject(Futryna);

	Futryna = new Obj3d(vec3(10, 0.01, -10.75), vec3(1, 1, 1), 90.f, 1.f);
	Futryna->load("../Resources/Models/futryna.obj");
	Futryna->textureName = "futryna";
	scene.AddObject(Futryna);

	Futryna = new Obj3d(vec3(10, 0.01, 5.75), vec3(1, 1, 1), 90.f, 1.f);
	Futryna->load("../Resources/Models/futryna.obj");
	Futryna->textureName = "futryna";
	scene.AddObject(Futryna);

	Futryna = new Obj3d(vec3(12.75, 0.01, 1), vec3(1, 1, 1), 0.f, 1.f);
	Futryna->load("../Resources/Models/futryna.obj");
	Futryna->textureName = "futryna";
	scene.AddObject(Futryna);

	Futryna = new Obj3d(vec3(12.75, 0.01, -5), vec3(1, 1, 1), 0.f, 1.f);
	Futryna->load("../Resources/Models/futryna.obj");
	Futryna->textureName = "futryna";
	scene.AddObject(Futryna);
	
	Obj3d* Sufit = new Obj3d(vec3(8,5,-2), vec3(1, 1, 1), 0.f, 1.5f);
	Sufit->load("../Resources/Models/sufit.obj");
	Sufit->textureName = "sufit";
	scene.AddObject(Sufit);

	Obj3d* Mebel = new Obj3d(vec3(0.20, 0, -7.5), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/Biblioteczka.obj");
	Mebel->textureName = "biblioteczka";
	scene.AddObject(Mebel);
	TextureManager::getInstance()->LoadTexture("futryna", "../Resources/Textures/futryna.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("sufit", "../Resources/Textures/Sufit.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("biblioteczka", "../Resources/Textures/Meble/Biblioteczka.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	Mebel = new Obj3d(vec3(3.6, 0, -7), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/DuzaSzafa.obj");
	Mebel->textureName = "duzaSzafa";
	scene.AddObject(Mebel);
	TextureManager::getInstance()->LoadTexture("duzaSzafa", "../Resources/Textures/Meble/DuzaSzafa.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(-4.75, 0, -2.75), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/Biurko.obj");
	Mebel->textureName = "Biurko";
	scene.AddObject(Mebel);
	TextureManager::getInstance()->LoadTexture("Biurko", "../Resources/Textures/Meble/Biurko.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(2.8, 0, 1.8), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/LozkoP.obj");
	Mebel->textureName = "LuzkoP";
	scene.AddObject(Mebel);
	TextureManager::getInstance()->LoadTexture("LuzkoP", "../Resources/Textures/Meble/LuzkoP.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(-1.5, 0, 2.2), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/Komoda.obj");
	Mebel->textureName = "Komoda";
	scene.AddObject(Mebel);
	TextureManager::getInstance()->LoadTexture("Komoda", "../Resources/Textures/Meble/Komoda.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(0.3, 0.05, -7.5), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/BookS.obj");
	Mebel->textureName = "BookS";
	scene.AddObject(Mebel);

	Mebel = new Obj3d(vec3(0.3, 0.65, -7.5), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/BookS.obj");
	Mebel->textureName = "BookS";
	scene.AddObject(Mebel);

	Mebel = new Obj3d(vec3(0.3, 1.23, -7.5), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/BookS.obj");
	Mebel->textureName = "BookS";
	scene.AddObject(Mebel);

	TextureManager::getInstance()->LoadTexture("BookS", "../Resources/Textures/Meble/BookS.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	//dodanie �mieci do jednego pokoju
	trashGen(-5.15, 5.4, -7.4, 2.4);


	//Sypialnia
	Mebel = new Obj3d(vec3(13, 0, 5.5), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/SzafaSyp.obj");
	Mebel->textureName = "SzafaSyp";
	scene.AddObject(Mebel);
	TextureManager::getInstance()->LoadTexture("SzafaSyp", "../Resources/Textures/Meble/SzafaSyp.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(20.75, 0, 5.1), vec3(1, 1, 1), 0.f, 0.95);
	Mebel->load("../Resources/Models/Meble/LozkoSyp.obj");
	Mebel->textureName = "LozkoSyp";
	scene.AddObject(Mebel);
	TextureManager::getInstance()->LoadTexture("LozkoSyp", "../Resources/Textures/Meble/LozkoSypTex.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(17.1, 0, -2.9), vec3(1, 1, 1), 180.f, 1.0);
	Mebel->load("../Resources/Models/Meble/KomodaD.obj");
	Mebel->textureName = "KomodaD";
	scene.AddObject(Mebel);
	TextureManager::getInstance()->LoadTexture("KomodaD", "../Resources/Textures/Meble/KomodaD.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(14.5, 0, -3), vec3(1, 1, 1), -90.f, 1);
	Mebel->load("../Resources/Models/Meble/Glosnik.obj");
	Mebel->textureName = "Glosnik";
	scene.AddObject(Mebel);

	Mebel = new Obj3d(vec3(19.5, 0, -3), vec3(1, 1, 1), -90.f, 1);
	Mebel->load("../Resources/Models/Meble/Glosnik.obj");
	Mebel->textureName = "Glosnik";
	scene.AddObject(Mebel);

	TextureManager::getInstance()->LoadTexture("Glosnik", "../Resources/Textures/Meble/Glosnik.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(13, 0, -16.5), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/Kanapa.obj");
	Mebel->textureName = "Kanapa";
	scene.AddObject(Mebel);

	TextureManager::getInstance()->LoadTexture("Kanapa", "../Resources/Textures/Meble/Kanapa.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(19, 0, -10), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/Stol.obj");
	Mebel->textureName = "Stol";
	scene.AddObject(Mebel);
	TextureManager::getInstance()->LoadTexture("Stol", "../Resources/Textures/Meble/Stol.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(17.85, 0, -8.75), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/Krzeslo.obj");
	Mebel->textureName = "Krzeslo";
	scene.AddObject(Mebel);

	Mebel = new Obj3d(vec3(17.85, 0, -10), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/Krzeslo.obj");
	Mebel->textureName = "Krzeslo";
	scene.AddObject(Mebel);

	Mebel = new Obj3d(vec3(17.85, 0, -11.25), vec3(1, 1, 1), 0.f, 1);
	Mebel->load("../Resources/Models/Meble/Krzeslo.obj");
	Mebel->textureName = "Krzeslo";
	scene.AddObject(Mebel);

	Mebel = new Obj3d(vec3(20.15, 0, -8.75), vec3(1, 1, 1), 180.f, 1);
	Mebel->load("../Resources/Models/Meble/Krzeslo.obj");
	Mebel->textureName = "Krzeslo";
	scene.AddObject(Mebel);

	Mebel = new Obj3d(vec3(20.15, 0, -10), vec3(1, 1, 1), 180.f, 1);
	Mebel->load("../Resources/Models/Meble/Krzeslo.obj");
	Mebel->textureName = "Krzeslo";
	scene.AddObject(Mebel);

	Mebel = new Obj3d(vec3(20.15, 0, -11.25), vec3(1, 1, 1), 180.f, 1);
	Mebel->load("../Resources/Models/Meble/Krzeslo.obj");
	Mebel->textureName = "Krzeslo";
	scene.AddObject(Mebel);

	TextureManager::getInstance()->LoadTexture("Krzeslo", "../Resources/Textures/Meble/Krzeslo.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(16., 0, -12.75), vec3(1, 1, 1), 180.f, 1);
	Mebel->load("../Resources/Models/Meble/StolKaw.obj");
	Mebel->textureName = "StolKaw";
	scene.AddObject(Mebel);

	TextureManager::getInstance()->LoadTexture("StolKaw", "../Resources/Textures/Meble/StolKaw.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Door *Drzwi;
	Drzwi = new Door(vec3(6.03, 0, -5.07), vec3(1, 1, 1), 0.f, 1);
	Drzwi->Obj3d::load("../Resources/Models/Door.obj");
	Drzwi->textureName = "Door";
	scene.AddDoor(Drzwi);

	Drzwi = new Door(vec3(12.9, 0, -3.9), vec3(1, 1, 1), 180.f, 1);
	Drzwi->Obj3d::load("../Resources/Models/Door.obj");
	Drzwi->textureName = "Door";
	scene.AddDoor(Drzwi);

	Drzwi = new Door(vec3(12.9, 0, 2.07), vec3(1, 1, 1), 180.f, 1);
	Drzwi->Obj3d::load("../Resources/Models/Door.obj");
	Drzwi->textureName = "Door";
	scene.AddDoor(Drzwi);

	Mebel = new Door(vec3(8.93, 0, -10.6), vec3(1, 1, 1), 90.f, 1);
	Mebel->load("../Resources/Models/Door.obj");
	Mebel->textureName = "Door";
	scene.AddObject(Mebel);

	Mebel = new Door(vec3(11.05, 0, 5.8), vec3(1, 1, 1), -90.f, 1);
	Mebel->load("../Resources/Models/Door.obj");
	Mebel->textureName = "Door";
	scene.AddObject(Mebel);

	TextureManager::getInstance()->LoadTexture("Door", "../Resources/Textures/Door.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	Mebel = new Obj3d(vec3(6.5, 1, -9.5), vec3(1, 1, 1), 180.f, 1);
	Mebel->load("../Resources/Models/Tablica.obj");
	Mebel->textureName = "Tablica";
	scene.AddObject(Mebel);

	Mebel = new Obj3d(vec3(6.5, 3, -9.5), vec3(1, 1, 1), 180.f, 1);
	Mebel->load("../Resources/Models/Tablica.obj");
	Mebel->textureName = "Tablica";
	scene.AddObject(Mebel);

	TextureManager::getInstance()->LoadTexture("Tablica", "../Resources/Textures/Tablica.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
}
void LoadColliders()
{
	//Obramowanie Mieszkania
	Col1 = new Collider(vec4(-5.75, -16.5, 21.5, -16.5), vec3(1.f, 0.f, 0.f)); //AB
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(21.5, -16.5, 21.5, 5.5), vec3(1.f, 0.f, 0.f)); //BC
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(21.5, 5.5, 6.5, 5.5), vec3(1.f, 0.f, 0.f)); //CD
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(6.5, 5.5, 6.5, -3.0), vec3(1.f, 0.f, 0.f)); //DE
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(6.5, -3.0, 6.0, -3.0), vec3(1.f, 0.f, 0.f)); //EF
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(6.0, -3.0, 6.0, 3.0), vec3(1.f, 0.f, 0.f)); //FG
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(6.0, 3.0, -5.75, 3.0), vec3(1.f, 0.f, 0.f)); //GH
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(-5.75, 3.0, -5.75, -16.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//Strefa A
	Col1 = new Collider(vec4(-5.75, -8.25, 6.5, -8.25), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(6.5, -8.25, 6.5, -5.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(6.5, -5, 6.0, -5.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(6.0, -5.0, 6.0, -8.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(6.0, -8.0, -5.75, -8), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//Strefa B
	Col1 = new Collider(vec4(1.0, -16.5, 1.0, -10.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(1.0, -10.5, 9.0, -10.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(9.0, -10.5, 9.0, -11.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(9.0, -11.0, 1.5, -11.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(1.5, -11.0, 1.5, -16.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//Strefa C
	Col1 = new Collider(vec4(12.5, -11.0, 11.0, -11.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(11.0, -11.0, 11.0, -10.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(11.0, -10.5, 12.5, -10.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//Strefa D
	Col1 = new Collider(vec4(12.5, -16.5, 12.5, -6.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(12.5, -6.0, 13.0, -6.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(13.0, -6.0, 13.0, -16.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//Strefa E
	Col1 = new Collider(vec4(12.5, -4.0, 13.0, -4.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(13.0, -4.0, 13.0, 0.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(13.0, 0.0, 12.5, 0.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(12.5, 0.0, 12.5, -4.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//Strefa F
	Col1 = new Collider(vec4(13.0, -2.25, 21.5, -2.25), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(13.0, -1.75, 21.5, -1.75), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//Strefa G
	Col1 = new Collider(vec4(13.0, 5.5, 13.0, 2.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(13.0, 2.0, 12.5, 2.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(12.5, 2.0, 12.5, 5.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//du�a szafa + p�ka z ksi��kami
	Col1 = new Collider(vec4(6, -6.0, 1.2, -6.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(1.2, -6.0, 1.2, -7.1), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(1.2, -7.1, -0.8, -7.1), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(-0.8, -7.1, -0.8, -8.0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//nogi ��ka
	SquareCollider(vec3(5.84, 0, 0.75), 0.11);
	SquareCollider(vec3(5.84, 0, 2.9), 0.11);
	SquareCollider(vec3(-0.25, 0, 0.75), 0.11);
	SquareCollider(vec3(-0.25, 0, 2.9), 0.11);

	//biurko �rodek
	Col1 = new Collider(vec4(-5.7, -2.7, -3.86, -2.7), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(-3.86, -2.7, -3.86, -2.84), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(-3.86, -2.84, -5.7, -2.84), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//biurko szafka prawa
	Col1 = new Collider(vec4(-5.7, -6.7, -3.86, -6.7), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(-3.86, -6.7, -3.86, -8), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//biurko szafka lewa
	Col1 = new Collider(vec4(-5.7, 1.82, -3.86, 1.82), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(-3.86, 1.82, -3.86, 3), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//komoda
	Col1 = new Collider(vec4(-2.5, 3, -2.5, 1.55), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(-2.5, 1.55, -0.5, 1.55), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(-0.5, 1.55, -0.5, 3), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);


	//sypialnia meble
	Col1 = new Collider(vec4(17.8, 5.52, 17.8, 4.63), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(17.8, 4.63, 16.15, 4.63), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(16.15, 4.63, 16.15, 4.25), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(16.15, 4.25, 15.0, 4.25), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(15.0, 4.25, 14.1, 3.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(14.1, 3.5, 13.0, 3.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	//nogi ��ka
	SquareCollider(vec3(18.4, 0, 5.1), 0.25);
	SquareCollider(vec3(20.72, 0, 5.1), 0.25);
	SquareCollider(vec3(20.72, 0, 0.8), 0.25);
	SquareCollider(vec3(18.4, 0, 0.8), 0.25);
	//Salon
	//Kolumny
	SquareCollider(vec3(14.5, 0, -3), 0.3);
	SquareCollider(vec3(19.5, 0, -3), 0.3);

	//szafka
	Col1 = new Collider(vec4(15.52, -2.25, 15.52, -3.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(15.52, -3.5, 18.6, -3.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(18.6, -3.5, 18.6, -2.25), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//krzes�a
	SquareCollider(vec3(17.9, 0, -8.75), 0.4);
	SquareCollider(vec3(17.9, 0, -10.0), 0.4);
	SquareCollider(vec3(17.9, 0, -11.25), 0.4);
	SquareCollider(vec3(20.1, 0, -8.75), 0.4);
	SquareCollider(vec3(20.1, 0, -10.0), 0.4);
	SquareCollider(vec3(20.1, 0, -11.25), 0.4);

	//st�
	SquareCollider(vec3(18, 0, -8), 0.05);
	SquareCollider(vec3(20, 0, -8), 0.05);
	SquareCollider(vec3(20, 0, -12), 0.05);
	SquareCollider(vec3(18, 0, -12), 0.05);

	//stolik do kawy
	SquareCollider(vec3(16.66, 0, -14.2), 0.05);
	SquareCollider(vec3(15.35, 0, -14.2), 0.05);
	SquareCollider(vec3(15.35, 0, -11.3), 0.05);
	SquareCollider(vec3(16.66, 0, -11.3), 0.05);

	//kanapa
	Col1 = new Collider(vec4(13, -10.82, 14.55, -10.82), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(14.55, -10.82, 14.55, -14.6), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(14.55, -14.6, 16.6, -14.6), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(16.6, -14.6, 16.6, -16.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//blokada �azienki ***Teren nie dodany
	Col1 = new Collider(vec4(9, -10.4, 11, -10.4), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);


	//blokada kuchni ***Teren nie dodany
	Col1 = new Collider(vec4(6.5, -8.25, 6.5, -10.5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
	//Drzwi Pok�j 3
	Col1 = new Collider(vec4(12.8, 2, 12.8, 0), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//Drzwi Pok�j 2
	Col1 = new Collider(vec4(12.8, -4, 12.8, -6), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);

	//Drzwi Pok�j 1
	Col1 = new Collider(vec4(6, -3, 6, -5), vec3(1.f, 0.f, 0.f)); //HA
	scene.AddCollider(Col1);
}
void trashGen(float x_min, float x_max, float z_min, float z_max)
{
	TrashGen * smiec;
	float x_pos;
	float z_pos;
	int ix_max, iz_max;
	for (int i = 0; i < 2000; i++)
	{
		ix_max = (x_max - x_min) * 1000;
		iz_max = (z_max - z_min) * 1000;
		ix_max = rand() % ix_max;
		iz_max = rand() % iz_max;
		x_pos = ((float)ix_max) / 1000 + x_min;
		z_pos = ((float)iz_max) / 1000 + z_min;
		smiec = new TrashGen(vec3(x_pos, 0.4, z_pos));
		scene.AddTrash(smiec);
	}
}
void checkCollisions()
{
	if (player->collide == true)
	{
		for (unsigned int i = 0; i < scene.colliders.size(); i++)
		{
			vec4 lineCords = scene.colliders[i]->getCords();
			if ((player->pos.x > min(lineCords.x1, lineCords.x2) - 0.7 && player->pos.x < max(lineCords.x1, lineCords.x2) + 0.7) &&
				(player->pos.z > min(lineCords.z1, lineCords.z2) - 0.7 && player->pos.z < max(lineCords.z1, lineCords.z2) + 0.7))
			{
				float pd1 = sqrt(((player->pos.x - lineCords.x1)*(player->pos.x - lineCords.x1)) + ((player->pos.z - lineCords.z1)*(player->pos.z - lineCords.z1)));
				float pd2 = sqrt(((player->pos.x - lineCords.x2)*(player->pos.x - lineCords.x2)) + ((player->pos.z - lineCords.z2)*(player->pos.z - lineCords.z2)));
				if (lineCords.x1 != lineCords.x2 && lineCords.z1 != lineCords.z2)
				{
					float d = abs(scene.colliders[i]->A*player->pos.x + scene.colliders[i]->B*player->pos.z + scene.colliders[i]->C) / sqrt(scene.colliders[i]->A*scene.colliders[i]->A + scene.colliders[i]->B*scene.colliders[i]->B);
					if (d <= player->radius &&
						player->pos.x >= min(lineCords.x1, lineCords.x2) - 0.25 && player->pos.x <= max(lineCords.x1, lineCords.x2) + 0.25
						&& player->pos.z >= min(lineCords.z1, lineCords.z2) - 0.25 && player->pos.z <= max(lineCords.z1, lineCords.z2) + 0.25)
					{
						player->pos.x = scene.colliders[i]->befcolx;
						player->pos.z = scene.colliders[i]->befcolz;
					}
					else if (pd1 < player->radius || pd2 < player->radius)
					{
						player->pos.x = scene.colliders[i]->befcolx;
						player->pos.z = scene.colliders[i]->befcolz;
					}
					else
					{
						scene.colliders[i]->befcolx = player->pos.x;
						scene.colliders[i]->befcolz = player->pos.z;
					}
				}
				else if (lineCords.x1 == lineCords.x2 && lineCords.z1 != lineCords.z2)
				{
					if (abs(player->pos.x - lineCords.x1) <= player->radius && player->pos.z >= min(lineCords.z1, lineCords.z2) && player->pos.z <= max(lineCords.z1, lineCords.z2))
					{
						player->pos.x = scene.colliders[i]->befcolx;
						player->pos.z = scene.colliders[i]->befcolz;
					}
					else if (pd1 < player->radius || pd2 < player->radius)
					{
						player->pos.x = scene.colliders[i]->befcolx;
						player->pos.z = scene.colliders[i]->befcolz;
					}
					else
					{
						scene.colliders[i]->befcolx = player->pos.x;
						scene.colliders[i]->befcolz = player->pos.z;
					}
				}
				else if (lineCords.x1 != lineCords.x2 && lineCords.z1 == lineCords.z2)
				{
					if (abs(player->pos.z - lineCords.z1) <= player->radius && player->pos.x >= min(lineCords.x1, lineCords.x2) && player->pos.x <= max(lineCords.x1, lineCords.x2))
					{
						player->pos.x = scene.colliders[i]->befcolx;
						player->pos.z = scene.colliders[i]->befcolz;
					}
					else if (pd1 < player->radius || pd2 < player->radius)
					{
						player->pos.x = scene.colliders[i]->befcolx;
						player->pos.z = scene.colliders[i]->befcolz;
					}
					else
					{
						scene.colliders[i]->befcolx = player->pos.x;
						scene.colliders[i]->befcolz = player->pos.z;
					}
				}
			}
		}
	}
}

clock_t first_point, bonusmoment;
void gainPoint()
{
	int j = 0;
	for (deque<TrashGen*>::iterator i = scene.smieci.begin(); i != scene.smieci.end(); i++)
	{
		float distance = sqrt(((scene.smieci[j]->pos.x - player->pos.x)*(scene.smieci[j]->pos.x - player->pos.x)) +
			((scene.smieci[j]->pos.z - player->pos.z)*(scene.smieci[j]->pos.z - player->pos.z)));
		if (distance < player->radius)
		{
			player->points++;
			scene.playerpoints = player->points;
			if (player->points % 1000 == 1)
				first_point = clock();
			if (player->points % 1000 == 0 && player->points > 0)
			{
				bonusmoment = clock();
				double time = (double(bonusmoment - first_point) / CLOCKS_PER_SEC);
				if(time < 60)
				{
					scene.hud.energy += 20;
				}
			}
			cout << player->points << endl;
			if (i != scene.smieci.end()||i!=scene.smieci.begin())
			{
				i=scene.smieci.erase(i);
				break;
			}
		}
		j++;
	}
}

float min(float x, float y)
{
	if (x <= y)return x;
	else return y;
}

float max(float x, float y)
{
	if (x >= y)return x;
	else return y;
}

void SquareCollider(vec3 p, float r)
{
	vec3 p1 = vec3(p.x - r, 0, p.z + r); //A
	vec3 p2 = vec3(p.x - r, 0, p.z - r); //B
	vec3 p3 = vec3(p.x + r, 0, p.z - r); //C
	vec3 p4 = vec3(p.x + r, 0, p.z + r); //D

	Col1 = new Collider(vec4(p1.x, p1.z, p2.x, p2.z), vec3(1.f, 0.f, 0.f)); //AB
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(p2.x, p2.z, p3.x, p3.z), vec3(1.f, 0.f, 0.f)); //BC
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(p3.x, p3.z, p4.x, p4.z), vec3(1.f, 0.f, 0.f)); //CD
	scene.AddCollider(Col1);
	Col1 = new Collider(vec4(p4.x, p4.z, p1.x, p1.z), vec3(1.f, 0.f, 0.f)); //DA
	scene.AddCollider(Col1);
}

void OpenDoorsCheck()
{
	for (unsigned int i = 0; i < scene.doors.size(); i++)
	{
		float distance = sqrt(((scene.doors[i]->pos.x - player->pos.x)*(scene.doors[i]->pos.x - player->pos.x)) +
			((scene.doors[i]->pos.z - player->pos.z)*(scene.doors[i]->pos.z - player->pos.z)));
		if (distance < player->radius * 4)
		{
			scene.doorunlock = true;
			scene.doorindex = i;
			break;
		}
		else
		{
			scene.doorunlock = false;
			scene.doorindex = -1;
		}
	}
}

