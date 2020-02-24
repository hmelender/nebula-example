#include "component.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"
#include "lightcomponent.h"
#include "message.h"

hm::Component::Component(Type type) : m_Entity(nullptr), m_Initialized(false), m_Type(type)
{
}

void hm::Component::SetTransform(const Math::matrix44& matrix)
{
	return;
}

hm::Component::operator hm::TransformComponent&()
{
	return *dynamic_cast<hm::TransformComponent*>(this);
}

hm::Component::operator hm::GraphicsComponent& ()
{
	return *dynamic_cast<hm::GraphicsComponent*>(this);
}

hm::Component::operator hm::LightComponent& ()
{
	return *dynamic_cast<hm::LightComponent*>(this);
}


