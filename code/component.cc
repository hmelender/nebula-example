#include "component.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"

hm::Component::Component() : m_Entity(nullptr), m_Initialized(false)
{
}

hm::Component::operator hm::TransformComponent&()
{
	return *dynamic_cast<hm::TransformComponent*>(this);
}


