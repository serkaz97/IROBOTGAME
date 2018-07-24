#pragma once
#include "stdafx.h"
class TrashGen : public SceneObject
{

public:
	TrashGen(vec3 pos);
TrashGen();
	~TrashGen();
	bool render;
	void Render();
	void Update();
	vec4 getCords() { return vec4(0, 0, 0, 0); };
};

