#include "stdafx.h"
#include "Door.h"


Door::Door(vec3 pos, vec3 color, float angle, float scale)
{
	this->pos = pos;
	this->color = color;
	this->scale = scale;
	this->angle = angle;
	this->Open = false;
	this->angle0 = angle;
}


Door::~Door()
{
}

void Door::Update()
{
	if (this->Open == true && angle <= angle0 + 135)
	{
		this->angle+=0.1;
	}
	else if (this->Open == false && angle > angle0)
	{
		angle-=0.1;
	}

}

