#pragma once
#include "Obj3d.h"
class Door: public Obj3d
{
public:
	Door(vec3 pos, vec3 color, float angle, float scale);
	~Door();
	bool Open;
	void Update();
	float angle0;
	bool openingdist;
	vec4 getCords() { return vec4(0, 0, 0, 0); }
};

