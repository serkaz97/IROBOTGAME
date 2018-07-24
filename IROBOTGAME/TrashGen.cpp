#include "stdafx.h"
#include "TrashGen.h"


TrashGen::TrashGen()
{
}

TrashGen::TrashGen(vec3 pos)
{
	this->render = true;
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->pos.z = pos.z;
}

TrashGen::~TrashGen()
{
}

void TrashGen::Render()
{
	if (render == true)
	{
		float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
		float mat_diffuse[] = { 0, 0, 1 };
		float mat_specular[] = { 0.1f, 0.1f, 0.1f };

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

		glColor3f(0, 0, 1);
		{
			glPushMatrix();
			glTranslatef(pos.x, 0, pos.z);
			glutSolidCube(0.01);
			glPopMatrix();
		}
	}
}

void TrashGen::Update()
{
	
}