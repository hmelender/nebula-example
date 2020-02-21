#include "entitymanager.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"

hm::EntityManager::EntityManager() : m_Initialized(false)
{

}

hm::EntityManager* hm::EntityManager::s_Instance = nullptr;

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
	e->m_Name = name;
	TransformComponent& t = *(TransformComponent*)&e->CreateComponent(Component::Type::TRANSFORM);

	size_t s = m_Entities.Size();
	m_Entities.Append(e);
	
	m_EntityTable.Add(name, s);

	e->Init();

	return *e;
}

hm::Entity& hm::EntityManager::CreateEntity(const StringAtom& name, const Resources::ResourceName& uri, const StringAtom& tag)
{
	return CreateEntity(name, uri, tag, point(0.0f, 0.0f, 0.0f));
}

hm::Entity& hm::EntityManager::CreateEntity(const StringAtom& name, const Resources::ResourceName& uri, const StringAtom& tag, const Math::point& position)
{
	Entity* e = Entity::Create();
	e->m_Name = name;
	TransformComponent& t = *(TransformComponent*)&e->CreateComponent(Component::Type::TRANSFORM);
	GraphicsComponent& g = *(GraphicsComponent*)&e->CreateComponent(Component::Type::GRAPHICS);


	size_t s = m_Entities.Size();
	m_Entities.Append(e);

	m_EntityTable.Add(name, s);

	e->Init();

	t.SetPosition(position);
	g.LoadModel(uri, tag);

	return *e;
}

hm::Entity& hm::EntityManager::GetEntity(const StringAtom& name)
{
	return *m_Entities[m_EntityTable[name]];
}

void hm::EntityManager::RemoveEntity(const StringAtom& name)
{
	IndexT idx = m_EntityTable[name];
	IndexT lastIdx = m_Entities.Size() - 1;
	Entity* e = m_Entities[idx];

	m_EntityTable.Erase(name);
	m_Entities.EraseIndexSwap(idx);
	if (e != nullptr)
		e->Shutdown();

	if (idx != lastIdx) {

		Entity* lastEntity = m_Entities[lastIdx];
		m_EntityTable[lastEntity->m_Name] = idx;
	}
}

void hm::EntityManager::RemoveEntity(Entity& entity)
{
	RemoveEntity(entity.m_Name);
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
	DispatchMessages();

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
