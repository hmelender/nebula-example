#include "entity.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"

namespace hm
{
	__ImplementClass(hm::Entity, 'HMET', Core::RefCounted)
}

hm::Entity::Entity()
{
}

void hm::Entity::Init()
{
	for (Component& c: m_Components) {
		c.Init();
	}
}

void hm::Entity::Update()
{
	for (Component& c : m_Components) {
		c.Update();
	}
}

void hm::Entity::Shutdown()
{
	for (Component& c : m_Components) {
		c.Shutdown();
	}
}

void hm::Entity::AddComponent(Component& component)
{
	component.m_Entity = this;
	m_Components.Append(component);
}

void hm::Entity::CreateComponent(Component::Type componentType)
{
	Component* c = nullptr;
	switch (componentType)
	{
	case hm::Component::TRANSFORM:
		c = new TransformComponent(); break;
	case hm::Component::GRAPHICS:
		c = new GraphicsComponent(); break;
	default: return;
	}
	c->m_Entity = this;
	m_Components.Append(*c);
	
}

void hm::Entity::ReceiveMessage(const Message& message)
{
	for (Component& c : m_Components) {
		c.ReceiveMessage(message);
	}
}

