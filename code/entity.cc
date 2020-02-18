#include "entity.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"

namespace hm
{
	__ImplementClass(hm::Entity, 'HMET', Core::RefCounted)
}

hm::Entity::Entity()
{
	CreateComponent(Component::Type::TRANSFORM);
}

void hm::Entity::Init()
{
	for (Component* c: m_Components) {
		c->Init();
	}
}

void hm::Entity::Update()
{
	for (Component* c : m_Components) {
		c->Update();
	}
}

void hm::Entity::Shutdown()
{
	for (Component* c : m_Components) {
		c->Shutdown();
	}
}

hm::Component& hm::Entity::GetComponent(const StringAtom& name)
{
	return *m_Components[m_ComponentTable[name]];
}

void hm::Entity::ReceiveMessage(const Message& message)
{
	for (Component* c : m_Components) {
		c->ReceiveMessage(message);
	}
}

