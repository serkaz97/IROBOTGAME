#pragma once
class Player :
	public SceneObject
{
public:
	Player();
	~Player();

	void Render();
	void Update();
	vec4 getCords() { return vec4(0, 0, 0, 0); }
	float radius = 0.6;
	vec3 dir;
	float speed;
	float befcolx;
	float befcolz;
	float velocity_vertical;
	float velocity_horizontal;
	void CheckCollision() {};
	bool flyingMode;
	bool collide;

	Obj3d *Irobot;
};

