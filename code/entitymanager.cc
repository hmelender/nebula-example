#include "entitymanager.h"

MyApp::EntityManager& MyApp::EntityManager::GetInstance()
{
	if (s_Instance == nullptr) {
		s_Instance = new EntityManager();
	}
	return *s_Instance;
}

MyApp::Entity& MyApp::EntityManager::CreateEntity()
{
	Entity::
}

void MyApp::EntityManager::Init()
{
}

void MyApp::EntityManager::Update()
{
}

void MyApp::EntityManager::Shutdown()
{
}
