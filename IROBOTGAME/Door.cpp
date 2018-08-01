#include "stdafx.h"
#include "Door.h"


Door::Door(vec3 pos, vec3 color, float angle, float scale)
{
	this->pos = pos;
	this->color = color;
	this->scale = scale;
	this->angle = angle;
	this->angle0 = angle;
}


Door::~Door()
{
}

void Door::Update()
{
	if (open && angle > angle0-100)
	{
		angle -= 0.5;
	}
	else if (!open && angle < angle0)
	{
		angle += 0.5;
	}
}