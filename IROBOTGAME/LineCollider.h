#pragma once
class LineCollider //:
	//public Collider
{
public:
	LineCollider(vec4 cords, vec3 color);
	~LineCollider();
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

};

