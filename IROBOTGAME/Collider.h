#pragma once
#include "stdafx.h"
class Collider
{
public:
	Collider();
	Collider(vec4 cords, vec3 color);
	~Collider();
	vec3 pos;
	vec4 cords;
	float a, b, A, B, C;
	vec3 color;
	void Render();
	void Update();
	vec4 getCords()
	{
		return cords;
	}
	float befcolx;
	float befcolz;
	bool render=true;

};

