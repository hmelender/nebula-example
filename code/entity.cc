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

hm::Component& hm::Entity::CreateComponent(hm::Component::Type componentType)
{
	hm::Component* c = nullptr;
	switch (componentType)
	{
	case hm::Component::Type::TRANSFORM:
		c = hm::TransformComponent::Create();
		m_ComponentTable.Add("transform", m_Components.Size());
		break;
	case hm::Component::Type::GRAPHICS:
		c = hm::GraphicsComponent::Create();
		m_ComponentTable.Add("graphics", m_Components.Size());
		break;
	}

	c->m_Entity = this;
	m_Components.Append(c);

	return *c;
}

hm::Component& hm::Entity::GetComponent(const StringAtom& name)
{
	return *m_Components[m_ComponentTable[name]];
}

bool hm::Entity::RegisterVariable(const StringAtom& name, Variant& value)
{
	if (m_Variables.Contains(name))
		return false;

	m_Variables.Add(name, Variant(value));
	return true;
};

void hm::Entity::ReceiveMessage(const Message& message)
{
	for (Component* c : m_Components) {
		c->ReceiveMessage(message);
	}
}

