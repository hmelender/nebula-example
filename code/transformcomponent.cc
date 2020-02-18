#include "transformcomponent.h"
#include "entity.h"

namespace hm
{
	__ImplementClass(hm::TransformComponent, 'HMTC', Core::RefCounted)
}

hm::TransformComponent::TransformComponent()
{
}

void hm::TransformComponent::Init()
{
	m_Position = float4::zerovector();
	m_Velocity = float4::zerovector();
	m_Scale = float4(1.0f, 1.0f, 1.0, 1.0);
	m_Rotation = quaternion::identity();

	m_Matrix = matrix44::identity();
	m_Entity->RegisterVariable("transform_position", Variant(m_Position));
	m_Entity->RegisterVariable("transform_velocity", Variant(m_Velocity));
	m_Entity->RegisterVariable("transform_scale", Variant(m_Scale));
	m_Entity->RegisterVariable("transform_rotation", Variant(m_Rotation));
	m_Entity->RegisterVariable("transform_matrix", Variant(m_Matrix));
}

void hm::TransformComponent::Update()
{
}

void hm::TransformComponent::Shutdown()
{
}

void hm::TransformComponent::ReceiveMessage(const Message& message)
{
}
