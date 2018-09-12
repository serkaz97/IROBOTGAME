#include "stdafx.h"
#include "Scene.h"



Scene::Scene(void)
{
	hud.energy = 100;
}


Scene::~Scene(void)
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		delete sceneObjects[i];

	sceneObjects.clear();
}

void Scene::AddObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}

void Scene::AddCollider(Collider* object)
{
	colliders.push_back(object);
}

void Scene::AddTrash(TrashGen* smiec)
{
	smieci.push_back(smiec);
}
void Scene::AddDoor(Door* door)
{
	doors.push_back(door);
}


void Scene::Render()
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->Render();
	for (unsigned int i = 0; i < colliders.size(); i++)
		colliders[i]->Render();
	for (size_t i=0; i <smieci.size(); i++)
	{
		smieci[i]->Render();
	}
	for (unsigned int i = 0; i < doors.size(); i++)
		doors[i]->Render();
}	

void Scene::Update()
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->Update();
	for (unsigned int i = 0; i < doors.size(); i++)
		doors[i]->Update();

	if (hud.energy >= 100)
	{
		hud.energy = 100;
	}
	if (hud.energy <= 0)
	{
		hud.energy = 0;
	}
}

void renderBitmapString(float x, float y, char* text) {
	char *c;
	glRasterPos3f(x, y, 0);
	for (c = text; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void renderBitmapString2(float x, float y, char* text) {
	char *c;
	glRasterPos3f(x, y, 0);
	for (c = text; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void Scene::guiDisplay()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, 0, -2);
	gluOrtho2D(0, 100, 0, 100);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glBegin(GL_QUADS);

	//WskaŸniki baterii
	//1
	if (hud.energy > 0)
	{
		glColor3f(0, 0.9, 0);
		glVertex2f(3, 97);
		glVertex2f(3, 93);
		glVertex2f(5, 93);
		glVertex2f(5, 97);
	}
	//2
	if (hud.energy > 25)
	{
		glVertex2f(6, 97);
		glVertex2f(6, 93);
		glVertex2f(8, 93);
		glVertex2f(8, 97);
	}
	//3
	if (hud.energy > 50)
	{
		glVertex2f(9, 97);
		glVertex2f(9, 93);
		glVertex2f(11, 93);
		glVertex2f(11, 97);
	}
	//4
	if (hud.energy > 75)
	{
		glVertex2f(12, 97);
		glVertex2f(12, 93);
		glVertex2f(14, 93);
		glVertex2f(14, 97);
	}

	//bateria t³o
	glColor3f(0, 0.1, 0);
	glVertex2f(1, 98);
	glVertex2f(1, 92);
	glVertex2f(16, 92);
	glVertex2f(16, 98);

	glVertex2f(16, 96);
	glVertex2f(16, 94);
	glVertex2f(17, 94);
	glVertex2f(17, 96);


	glEnd();
	char text[50];
	sprintf(text, "%d fps", (int)hud.fps);

	glColor3f(1, 1, 1);
	renderBitmapString(90, 95, text);

	char text2[50];
	sprintf(text2, "energy: %d ", (int)hud.energy);

	char text3[30];
	sprintf(text3, "points: %d: ", playerpoints);

	char text4[50];
	sprintf(text4, "GAME OVER\n Your Score: %d", playerpoints);

	glColor3f(1, 1, 1);
	renderBitmapString(90, 95, text);
	renderBitmapString(1, 89, text2);
	renderBitmapString(1, 84, text3);

	if (hud.energy < 1)
	{
		glColor3f(1, 0, 0);
		renderBitmapString2(35, 50, text4);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}