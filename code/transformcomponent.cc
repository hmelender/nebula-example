#include "transformcomponent.h"
#include "graphicscomponent.h"
#include "entity.h"
#include "message.h"

namespace hm
{
	__ImplementClass(hm::TransformComponent, 'HMTC', Core::RefCounted)
}

hm::TransformComponent::TransformComponent() : hm::Component(Type::TRANSFORM), m_InMotion(false), m_UpdateMatrix(false), m_Transformable(nullptr)
{
	m_Matrix = matrix44::identity();
	m_Velocity = float4::zerovector();
	m_Rotation = quaternion::identity();
	m_Scale = vector(1.0f);
}

void hm::TransformComponent::Init()
{
	if (m_Initialized)
		return;

	m_Initialized = true;
	m_UpdateMatrix = true;
}

void hm::TransformComponent::Update()
{
	if (m_InMotion) {
		m_Position += m_Velocity;

		if (!m_UpdateMatrix)
			m_Matrix.translate(m_Velocity);
	}

	if (m_UpdateMatrix) {
		m_Matrix = matrix44::transformation(m_Pivot, Math::quaternion::identity(), m_Scale, m_Pivot, m_Rotation, m_Position);
		m_UpdateMatrix = false;
		if (m_Transformable != nullptr)
			m_Transformable->SetTransform(m_Matrix);
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
	m_Position = position;
	m_Matrix.set_position(m_Position);
}

void hm::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = point(x, y, z);
	m_Matrix.set_position(m_Position);
}

void hm::TransformComponent::Translate(const float4& vector)
{
	m_Position += vector;
	m_Matrix.translate(vector);
}

void hm::TransformComponent::Translate(float x, float y, float z)
{
	m_Position = point(x, y, z);
	m_Matrix.set_position(m_Position);
}

void hm::TransformComponent::SetVelocity(const float4& vector)
{
	m_Velocity = vector;
	m_InMotion = (m_Velocity[0] != 0.0f || m_Velocity[1] != 0.0f || m_Velocity[2] != 0.0f);
}

void hm::TransformComponent::SetRotation(const quaternion& rotation)
{
	m_Rotation = rotation;
	m_UpdateMatrix = true;
}

void hm::TransformComponent::SetRotationEuler(float x, float y, float z)
{
	m_Rotation = quaternion::rotationyawpitchroll(x, y, z);
	m_UpdateMatrix = true;
}

void hm::TransformComponent::RotateAxis(const float4& axis, float angle)
{
	m_Rotation = quaternion::multiply(m_Rotation, quaternion::rotationaxis(axis, angle));
	m_UpdateMatrix = true;
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
	m_Rotation = quaternion::multiply(m_Rotation, quaternion::rotationaxis(axisVec, angle));
	m_UpdateMatrix = true;
}

void hm::TransformComponent::SetScale(float scale)
{
	m_Scale = vector(scale);
	m_UpdateMatrix = true;
}

void hm::TransformComponent::SetScale(const float4& scale)
{
	m_Scale = scale;
	m_UpdateMatrix = true;
}

void hm::TransformComponent::SetScale(float x, float y, float z)
{
	m_Scale = vector(x, y, z);
	m_UpdateMatrix = true;
}

void hm::TransformComponent::SetPivot(const point& position)
{
	m_Pivot = position;
	m_UpdateMatrix = true;
}

void hm::TransformComponent::Serialize(Serializer& writer)
{
	writer.AddNode("transform");
	writer.AddData("position", m_Position);
	writer.AddData("scale", m_Scale);
	writer.AddData("rotation", m_Rotation);
	writer.AddData("velocity", m_Velocity);
	writer.AddData("pivot", m_Pivot);
	writer.EndNode();
}

void hm::TransformComponent::Deserialize(Serializer& reader)
{
	reader.GetData("position", m_Position);
	reader.GetData("scale", m_Scale);
	reader.GetData("rotation", m_Rotation);
	reader.GetData("velocity", m_Velocity);
	reader.GetData("pivot", m_Pivot);
	m_UpdateMatrix = true;
}
