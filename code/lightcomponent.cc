#include "lightcomponent.h"
#include "transformcomponent.h"
#include "entity.h"
#include "message.h"

namespace hm
{
	__ImplementClass(hm::LightComponent, 'HMLC', Core::RefCounted)
}

void hm::LightComponent::SetTransform(const Math::matrix44& matrix)
{
	Lighting::LightContext::SetTransform(m_LightId, matrix);
}

hm::LightComponent::LightComponent() : hm::Component(Type::LIGHT)
{
}

void hm::LightComponent::Init()
{
	if (m_Initialized)
		return;
	
	m_LightId = Graphics::CreateEntity();
	Lighting::LightContext::RegisterEntity(m_LightId);
	m_Initialized = true;
}

void hm::LightComponent::Update()
{
}

void hm::LightComponent::Shutdown()
{
	Graphics::DeregisterEntity<ModelContext, ObservableContext>(m_LightId);
	Graphics::DestroyEntity(m_LightId);
}

void hm::LightComponent::ReceiveMessage(const Message& message)
{
}

hm::LightComponent& hm::LightComponent::operator=(const hm::Component& rhs)
{
	return *(LightComponent*)(&rhs);
}

void hm::LightComponent::SetupPointLight(const Math::float4& color, float intensity, const Math::point& position, float range, bool castShadows)
{
	TransformComponent& t = m_Entity->GetComponent("transform");
	t.SetPosition(position);
	t.m_Transformable = this;
	Lighting::LightContext::SetupPointLight(m_LightId, color, intensity, t.m_Matrix, range, castShadows);

}

