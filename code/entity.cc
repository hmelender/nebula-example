#include "entity.h"
#include "entitymanager.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"
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

hm::Component& hm::Entity::CreateComponent(hm::Component::Type componentType)
{
	hm::Component* c = nullptr;
	switch (componentType)
	{
	case hm::Component::Type::TRANSFORM: {
		c = hm::TransformComponent::Create();
		StringAtom atm = StringAtom("transform");
		if (!m_ComponentTable.Contains(atm))
			m_ComponentTable.Add(atm, m_Components.Size());
	}
		break;
	case hm::Component::Type::GRAPHICS: {
		c = hm::GraphicsComponent::Create();
		StringAtom atm = StringAtom("graphics");
		if (!m_ComponentTable.Contains(atm))
			m_ComponentTable.Add(atm, m_Components.Size());
	}
		break;
	}
	if (c != nullptr)
		c->m_Entity = this;
		m_Components.Append(c);
		return *c;
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
