#pragma once
class Door: public Obj3d
{
public:
	Door(vec3 pos, vec3 color, float angle, float scale);
	~Door();

	float angle0;
	bool open;
	bool unlock;
	void Update();
};

