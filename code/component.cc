#include "component.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"
#include "message.h"

hm::Component::Component(Type type) : m_Entity(nullptr), m_Initialized(false), m_Type(type)
{
}

hm::Component::operator hm::TransformComponent&()
{
	return *dynamic_cast<hm::TransformComponent*>(this);
}


