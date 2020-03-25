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
	Lighting::LightContext::DeregisterEntity(m_LightId);
	// Graphics::DestroyEntity(m_LightId);
}

void hm::LightComponent::ReceiveMessage(const Message& message)
{
}

hm::LightComponent& hm::LightComponent::operator=(const hm::Component& rhs)
{
	return *(LightComponent*)(&rhs);
}

void hm::LightComponent::SetupPointLight(const Math::float4& color, float intensity, float range, bool castShadows)
{
	TransformComponent& t = m_Entity->GetComponent(Type::TRANSFORM);
	t.m_Transformable = this;
	m_Color = color;
	m_Intensity = intensity;
	m_Range = range;
	m_CastShadows = castShadows;

	Lighting::LightContext::SetupPointLight(m_LightId, m_Color, m_Intensity, t.m_Matrix, m_Range, m_CastShadows);

}

void hm::LightComponent::Serialize(Serializer& writer)
{
	writer.AddNode("light");
	writer.AddData("color", m_Color);
	writer.AddData("intensity", m_Intensity);
	writer.AddData("range", m_Range);
	writer.AddData("cast_shadows", m_CastShadows);
	writer.EndNode();
}

void hm::LightComponent::Deserialize(Serializer& reader)
{
	Math::float4 color;
	float intensity = 0.0f;
	float range = 0.0f;
	bool castShadows = false;

	reader.GetData("color", color);
	reader.GetData("intensity", intensity);
	reader.GetData("range", range);
	reader.GetData("cast_shadows", castShadows);

	SetupPointLight(color, intensity, range, castShadows);

}

