#include "entity.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"

MyApp::Entity::Entity()
{
}

void MyApp::Entity::Init()
{
	for (Component& c: m_Components) {
		c.Init();
	}
}

void MyApp::Entity::Update()
{
	for (Component& c : m_Components) {
		c.Update();
	}
}

void MyApp::Entity::Shutdown()
{
	for (Component& c : m_Components) {
		c.Shutdown();
	}
}

void MyApp::Entity::AddComponent(Component& component)
{
	component.m_Entity = this;
	m_Components.Append(component);
}

void MyApp::Entity::CreateComponent(Component::Type componentType)
{
	Component* c = nullptr;
	switch (componentType)
	{
	case MyApp::Component::TRANSFORM:
		c = new TransformComponent(); break;
	case MyApp::Component::GRAPHICS:
		c = new GraphicsComponent(); break;
	default: return;
	}
	c->m_Entity = this;
	m_Components.Append(*c);
	
}

void MyApp::Entity::ReceiveMessage(const Message& message)
{
	for (Component& c : m_Components) {
		c.ReceiveMessage(message);
	}
}

