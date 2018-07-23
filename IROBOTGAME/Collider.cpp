#include "stdafx.h"
#include "Collider.h"


Collider::Collider()
{
}

Collider::Collider(vec4 cords, vec3 color)
{
	this->pos.x = (cords.x1 + cords.x2) / 2;
	this->pos.z = (cords.z1 + cords.z2) / 2;
	this->pos.y = 0;
	this->color = color;
	this->cords = cords;
	this->befcolx = cords.x1+2;
	this->befcolz = cords.z1+2;
	if (cords.x1 != cords.x2)
	{
		this->a = (cords.z2 - cords.z1) / (cords.x2 - cords.x1);
		this->b = cords.z1 - a*cords.x1;
		this->A = -a;
		this->B = 1;
		this->C = -b;
	}
	else
	{
		this->a = 0;
		this->b = 0;
		this->A = 0;
		this->B = 0;
		this->C = 0;
	}
}
Collider::~Collider()
{
}

void Collider::Render()
{
	if (render == true)
	{
		float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
		float mat_diffuse[] = { color.x, color.y, color.z };
		float mat_specular[] = { 0.1f, 0.1f, 0.1f };

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glTranslatef(0, 0, 0);
		glLineWidth(1.5);
		glBegin(GL_LINES);
		glVertex3f(cords.x1, 0, cords.z1);
		glVertex3f(cords.x2, 0, cords.z2);
		glEnd();

		glColor3f(1, 1, 1);
		//A 
		{
			glPushMatrix();
			glTranslatef(cords.x1, 0, cords.z1);
			glutSolidSphere(0.01, 6, 6);
			glPopMatrix();
		}
		//B
		{
			glPushMatrix();
			glTranslatef(cords.x2, 0, cords.z2);
			glutSolidSphere(0.01, 6, 6);
			glPopMatrix();
		}
	}
	
}

void Collider::Update()
{

}
