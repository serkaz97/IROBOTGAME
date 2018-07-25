#include "stdafx.h"



Player::Player()
{
	
	pos.x = 8.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	befcolx = pos.x;
	befcolz = pos.z;
	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = -1.0f;
	points = 0;
	speed = .05f;

	velocity_horizontal = 0;
	velocity_vertical = 0;
	collide = true;
	flyingMode = false;

	Irobot = new Obj3d(vec3(pos.x, pos.y, pos.z), vec3(0.1, 0.1, 0.1), 0, 1.f);
	Irobot->load("../Resources/Models/Irobot.obj");
}


Player::~Player()
{
}

void Player::Render()
{
	Irobot->color = vec3(1, 0, 0);
	Irobot->Render();
	glPushMatrix();
	glTranslatef(pos.x, pos.y+0.1, pos.z);

	glutSolidSphere(0.2, 16, 16);
	glColor3f(1, 0, 0);
		glPushMatrix();
		glTranslated(0.5, 0, 0);
		glutSolidCube(0.1);
		glPopMatrix();
		glPushMatrix();
		glTranslated(-0.5, 0, 0);
		glutSolidCube(0.1);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, 0, 0.5);
		glutSolidCube(0.1);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, 0, -0.5);
		glutSolidCube(0.1);
		glPopMatrix();
	glPopMatrix();
}

void Player::Update()
{
	pos.x += dir.x * speed * velocity_vertical;
	pos.z += dir.z * speed * velocity_vertical;

	pos.x += dir.z * speed * velocity_horizontal;
	pos.z -= dir.x * speed * velocity_horizontal;

	if (flyingMode)
		pos.y += dir.y * speed * velocity_vertical;
	else
		pos.y = 0;
	Irobot->angle = dir.y;
	velocity_vertical /= 1.2;
	velocity_horizontal /= 1.2;
	Irobot->pos.x = pos.x;
	Irobot->pos.y = pos.y;
	Irobot->pos.z = pos.z;
}

