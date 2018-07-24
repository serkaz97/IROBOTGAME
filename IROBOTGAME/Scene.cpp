#include "stdafx.h"
#include "Scene.h"


Scene::Scene(void)
{
}


Scene::~Scene(void)
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		delete sceneObjects[i];

	sceneObjects.clear();
}

void Scene::AddObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}

void Scene::AddCollider(Collider* object)
{
	colliders.push_back(object);
}
void Scene::AddTrash(TrashGen* smiec)
{
	smieci.push_back(smiec);
}

void Scene::Render()
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->Render();
	for (unsigned int i = 0; i < colliders.size(); i++)
		colliders[i]->Render();
	for (size_t i=0; i <smieci.size(); i++)
	{
		smieci[i]->Render();
	}
}	

void Scene::Update()
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->Update();
}