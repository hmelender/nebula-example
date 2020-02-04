#include "entity.h"

MyApp::Entity::Entity()
{
}

void MyApp::Entity::Init()
{
	for (BaseComponent& c: m_Components) {
		c.Init();
	}
}

void MyApp::Entity::Update()
{
	for (BaseComponent& c : m_Components) {
		c.Update();
	}
}

void MyApp::Entity::Shutdown()
{
	for (BaseComponent& c : m_Components) {
		c.Shutdown();
	}
}
