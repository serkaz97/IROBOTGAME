#pragma once
#pragma once
class Drzwi :
	public SceneObject
{
public:
	Drzwi()
	{

	}
	Drzwi(vec3 pos, vec3 color, float angle, float scale);
	~Drzwi();

	bool load(std::string filepath);
	float scale;
	float angle;
	void Render();
	void Update();
	vec4 getCords() { return vec4(0, 0, 0, 0); }
	void CheckCollision() {};
	GLuint id = glGenLists(1);
	vec3 color;
	std::string textureName;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;
};
