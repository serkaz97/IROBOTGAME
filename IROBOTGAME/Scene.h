#pragma once
class Scene: public SceneObject
{
public:
	Scene(void);
	~Scene(void);

	void Render();
	void Update();
	void CheckCollision(){}
	void AddObject(SceneObject* object);
	void AddCollider(Collider* collider);
	vec4 getCords() { return vec4(0, 0, 0, 0); }
	std::vector<Collider*> colliders;
private:
	std::vector<SceneObject*> sceneObjects;

};

