#include "entitymanager.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"

hm::EntityManager::EntityManager() : m_Initialized(false)
{

}


hm::EntityManager& hm::EntityManager::GetInstance()
{
	if (s_Instance == nullptr) {
		s_Instance = new EntityManager();
	}
	return *s_Instance;
}

hm::Entity& hm::EntityManager::CreateEntity(const StringAtom& name)
{
	Entity* e = Entity::Create();
	TransformComponent& t = e->CreateComponent<TransformComponent>(Component::Type::TRANSFORM);

	size_t s = m_Entities.Size();
	m_Entities.Append(e);
	
	m_EntityTable.Add(name, s);

	if (m_Initialized)
		e->Init();

	return *e;
}

hm::Entity& hm::EntityManager::CreateEntity(const StringAtom& name, const Resources::ResourceName& uri, const StringAtom& tag)
{
	Entity* e = Entity::Create();
	TransformComponent& t = e->CreateComponent<TransformComponent>(Component::Type::TRANSFORM);
	GraphicsComponent& g = e->CreateComponent<GraphicsComponent>(Component::Type::GRAPHICS);
	

	size_t s = m_Entities.Size();
	m_Entities.Append(e);

	m_EntityTable.Add(name, s);

	if (m_Initialized)
		e->Init();

	g.LoadModel(uri, tag);

	return *e;
}

hm::Entity& hm::EntityManager::GetEntity(const StringAtom& name)
{
	return *m_Entities[m_EntityTable[name]];
}

void hm::EntityManager::RemoveEntity(const StringAtom& name)
{
	size_t s = m_EntityTable[name];
	Entity* e = m_Entities[s];
	if (e == nullptr)
		return
	e->Shutdown();
	m_EntityTable.Erase(name);
	m_Entities.EraseIndex(s);
}

void hm::EntityManager::Init()
{
	for (Entity* e : m_Entities) {
		e->Init();
	}
	m_Initialized = true;
}

void hm::EntityManager::Update()
{
	for (Entity* e : m_Entities) {
		e->Update();
	}
}

void hm::EntityManager::Shutdown()
{
	for (Entity* e : m_Entities) {
		e->Shutdown();
	}
}
