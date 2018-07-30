#pragma once
class SceneObject
{
public:
	SceneObject();
	~SceneObject();

	vec3 pos;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	virtual vec4 getCords() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;

};

