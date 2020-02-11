#include "entitymanager.h"

hm::EntityManager& hm::EntityManager::GetInstance()
{
	if (s_Instance == nullptr) {
		s_Instance = new EntityManager();
	}
	return *s_Instance;
}

hm::Entity& hm::EntityManager::CreateEntity()
{

}

void hm::EntityManager::Init()
{
}

void hm::EntityManager::Update()
{
}

void hm::EntityManager::Shutdown()
{
}
