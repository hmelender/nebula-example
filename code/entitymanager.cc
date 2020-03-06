#include "entitymanager.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"
#include "charactercomponent.h"
#include "lightcomponent.h"

hm::EntityManager::EntityManager() : m_Initialized(false)
{

}

hm::EntityManager* hm::EntityManager::s_Instance = nullptr;

float hm::EntityManager::frameDelta = 0.0f;

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
	TransformComponent& t = e->CreateComponent(Component::Type::TRANSFORM);

	size_t s = m_Entities.Size();
	m_Entities.Append(e);
	
	m_EntityTable.Add(name, s);

	e->Init();

	return *e;
}

hm::Entity& hm::EntityManager::CreateEntity(const StringAtom& name, const StringAtom& uri, const StringAtom& tag)
{
	return CreateEntity(name, uri, tag, point(0.0f, 0.0f, 0.0f));
}

hm::Entity& hm::EntityManager::CreateEntity(const StringAtom& name, const StringAtom& uri, const StringAtom& tag, const Math::point& position)
{
	Entity* e = Entity::Create();
	e->m_Name = name;
	TransformComponent& t = e->CreateComponent(Component::Type::TRANSFORM);
	GraphicsComponent& g = e->CreateComponent(Component::Type::GRAPHICS);


	size_t s = m_Entities.Size();
	m_Entities.Append(e);

	m_EntityTable.Add(name, s);

	e->Init();

	t.SetPosition(position);
	g.LoadModel(uri, tag);

	return *e;
}

hm::Entity& hm::EntityManager::CreateCharacter(const StringAtom& name, const StringAtom& modelUri, const StringAtom& skeletonUri, const StringAtom& animationUri, const StringAtom& tag, const Math::point& position)
{
	Entity* e = Entity::Create();
	e->m_Name = name;
	TransformComponent& t = e->CreateComponent(Component::Type::TRANSFORM);
	GraphicsComponent& g = e->CreateComponent(Component::Type::GRAPHICS);
	CharacterComponent& c = e->CreateComponent(Component::Type::CHARACTER);

	size_t s = m_Entities.Size();
	m_Entities.Append(e);

	m_EntityTable.Add(name, s);

	e->Init();

	t.SetPosition(position);
	g.LoadModel(modelUri, tag);
	c.LoadCharacter(skeletonUri, animationUri, tag);

	return *e;
}

hm::Entity& hm::EntityManager::CreatePointLight(const StringAtom& name, const Math::float4& color, float intensity, const Math::point& position, float range, bool castShadows)
{
	Entity& e = CreateEntity(name);
	TransformComponent& t = e.GetComponent(Component::Type::TRANSFORM);
	t.SetPosition(position);

	LightComponent& l = e.CreateComponent(Component::Type::LIGHT);
	l.SetupPointLight(color, intensity, range, castShadows);
	return e;
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
	Entity* lastEntity = m_Entities[lastIdx];

	m_EntityTable.Erase(name);
	m_Entities.EraseIndexSwap(idx);
	if (e != nullptr)
		e->Shutdown();

	if (idx != lastIdx) {
		m_EntityTable[lastEntity->m_Name] = idx;
	}
}

void hm::EntityManager::RemoveEntity(Entity& entity)
{
	RemoveEntity(entity.m_Name);
}

void hm::EntityManager::SaveSceneState(const char* file)
{
	m_Serializer.BeginWrite(file);
	m_Serializer.AddNode("scene");

	for (Entity* e : m_Entities) {
		e->Serialize(m_Serializer);
	}
	m_Serializer.EndNode();

	m_Serializer.End();
}

void hm::EntityManager::LoadSceneState(const char* file)
{
	Shutdown();

	m_Serializer.BeginRead(file);
	m_Serializer.Child();
	m_Serializer.Child();

	do {
		Util::String name = m_Serializer.GetName();
		m_Serializer.GetData("name", name);
		Entity& e = CreateEntity(name);
		e.Deserialize(m_Serializer);

	} while (m_Serializer.Next());

	m_Serializer.End();

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
	m_Entities.Clear();
	m_EntityTable.Clear();
}
