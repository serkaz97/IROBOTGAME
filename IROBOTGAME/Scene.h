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
	void Render();
	void Update();
	void CheckCollision(){}
	void AddObject(SceneObject* object);
	void AddCollider(Collider* collider);
	void AddDoor(Door* door);
	void AddTrash(TrashGen* trash);
	void guiDisplay();
	vec4 getCords() { return vec4(0, 0, 0, 0); }
	std::vector<Collider*> colliders;
	std::vector<Door*> doors;
	std::deque<TrashGen*> smieci;
private:
	std::vector<SceneObject*> sceneObjects;


};

