#pragma once


class Scene: public SceneObject
{
public:
	Scene(void);
	~Scene(void);
	struct HUD
	{
		float energy;
		float fps;
	}hud;
	std::vector<Collider*> colliders;
	std::deque<TrashGen*> smieci;

	void Render();
	void Update();
	void CheckCollision(){}
	void AddObject(SceneObject* object);
	void AddCollider(Collider* collider);

	void AddTrash(TrashGen* trash);
	void guiDisplay();
	vec4 getCords() { return vec4(0, 0, 0, 0); }

private:
	std::vector<SceneObject*> sceneObjects;


};

