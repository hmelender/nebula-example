#include "entity.h"
#include "entitymanager.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"
#include "lightcomponent.h"
#include "pybind11.h"
#include "message.h"

namespace hm
{
	__ImplementClass(hm::Entity, 'HMET', Core::RefCounted)
}

hm::Entity::Entity() : m_Initialized(false)
{
}

void hm::Entity::Init()
{
	if (m_Initialized)
		return;

	RegisterMessageHandler();
	SubscribeToMsgTypes(Message::Type::DEFAULT | Message::Type::DESTROY);

	for (Component* c: m_Components) {
		c->Init();
	}

	m_Initialized = true;
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

hm::Component& hm::Entity::CreateComponent(hm::Component::Type type)
{
	hm::Component* c = nullptr;
	const char* name = "none";
	switch (type)
	{
	case hm::Component::Type::TRANSFORM: {
		c = hm::TransformComponent::Create();
		name = "transform";
	}
		break;
	case hm::Component::Type::GRAPHICS: {
		c = hm::GraphicsComponent::Create();
		name = "graphics";
	}
		break;
	case hm::Component::Type::LIGHT: {
		c = hm::LightComponent::Create();
		name = "light";
	}
		break;
	}

	if (c != nullptr) {

		if (!m_ComponentTable.Contains(name))
			m_ComponentTable.Add(name, m_Components.Size());
		c->m_Entity = this;
		m_Components.Append(c);
		if (m_Initialized) c->Init();
	}
	return *c;
}

hm::Component& hm::Entity::GetComponent(Component::Type type)
{
	for (Component* c : m_Components) {
		if (c->m_Type == type)
			return *c;
	}
	return *static_cast<Component*>(nullptr); // ehh
}

hm::Component& hm::Entity::GetComponent(const StringAtom& name)
{
	return *m_Components[m_ComponentTable[name]];
}

void hm::Entity::ReceiveMessage(const Message& message)
{
	for (Component* c : m_Components) {
		if (message.m_ComponentType == c->m_Type)
			c->ReceiveMessage(message);
	}

	if (message.m_MessageType == Message::Type::DESTROY)
		hm::EntityManager::GetInstance().RemoveEntity(*this);
}
