#include "transformcomponent.h"
#include "graphicscomponent.h"
#include "entity.h"
#include "message.h"

namespace hm
{
	__ImplementClass(hm::TransformComponent, 'HMTC', Core::RefCounted)
}

hm::TransformComponent::TransformComponent() : hm::Component(Type::TRANSFORM), m_Matrix(nullptr), m_InMotion(false), m_Transformable(nullptr)
{
}

void hm::TransformComponent::Init()
{
	if (m_Initialized)
		return;

	m_Velocity = float4::zerovector();

	m_Entity->RegisterVariable("transform_velocity", m_Velocity);
	m_Matrix = &m_Transform.getmatrix();
	m_Entity->RegisterVariable("transform_matrix", *m_Matrix);

	m_Initialized = true;
}

void hm::TransformComponent::Update()
{
	if (m_InMotion) {
		point p = m_Transform.getposition() + m_Velocity;
		m_Transform.setposition(p);
	}

	if (m_Transform.isdirty()) {
		m_Matrix = &(m_Transform.getmatrix());
		if (m_Transformable != nullptr)
			m_Transformable->SetTransform(*m_Matrix);
	}

}

void hm::TransformComponent::Shutdown()
{
}

void hm::TransformComponent::ReceiveMessage(const Message& message)
{
}

void hm::TransformComponent::SetPosition(const point& position)
{
	m_Transform.setposition(position);
}

void hm::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Transform.setposition(point(x, y, z));
}

void hm::TransformComponent::Translate(const float4& vector)
{
	point p = m_Transform.getposition() + vector;
	m_Transform.setposition(p);
}

void hm::TransformComponent::Translate(float x, float y, float z)
{
	point p = m_Transform.getposition();
	p[0] += x;
	p[1] += y;
	p[2] += z;
	m_Transform.setposition(p);
}

void hm::TransformComponent::SetVelocity(const float4& vector)
{
	m_Velocity = vector;
	m_InMotion = (m_Velocity[0] != 0.0f || m_Velocity[1] != 0.0f || m_Velocity[2] != 0.0f);
}

void hm::TransformComponent::SetRotation(const quaternion& rotation)
{
	m_Transform.setrotate(rotation);
}

void hm::TransformComponent::SetRotationEuler(float x, float y, float z)
{
	m_Transform.setrotate(quaternion::rotationyawpitchroll(x, y, z));
}

void hm::TransformComponent::RotateAxis(float4 axis, float angle)
{
	m_Transform.setrotate(quaternion::multiply(m_Transform.getrotate(), quaternion::rotationaxis(axis, angle)));
}

void hm::TransformComponent::RotateAxis(hm::TransformComponent::Axis axis, float angle)
{
	float4 axisVec;
	switch (axis)
	{
	case hm::TransformComponent::Axis::Y:
		axisVec = float4(0.0f, 1.0f, 0.0f, 0.0f);
		break;
	case hm::TransformComponent::Axis::Z:
		axisVec = float4(0.0f, 0.0f, 1.0f, 0.0f);
		break;
	case hm::TransformComponent::Axis::X:
		axisVec = float4(1.0f, 0.0f, 0.0f, 0.0f);
		break;
	default:
		return;
	}
	m_Transform.setrotate(quaternion::multiply(m_Transform.getrotate(), quaternion::rotationaxis(axisVec, angle)));
}

void hm::TransformComponent::SetScale(float scale)
{
	m_Transform.setscale(vector(scale));

}

void hm::TransformComponent::SetScale(const float4& scale)
{
	m_Transform.setscale(scale);
}

void hm::TransformComponent::SetScale(float x, float y, float z)
{
	m_Transform.setscale(vector(x, y, z));
}

void hm::TransformComponent::SetPivot(const point& position)
{
	m_Transform.setrotatepivot(position);
	m_Transform.setscalepivot(position);
}
