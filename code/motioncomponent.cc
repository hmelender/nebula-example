#include "game.h"
#include "entitymanager.h"
#include "motioncomponent.h"
#include "transformcomponent.h"
#include "entity.h"
#include "message.h"

namespace hm
{
	__ImplementClass(hm::MotionComponent, 'HMMC', Core::RefCounted)
}

hm::MotionComponent::MotionComponent() : hm::Component(Type::MOTION), m_InMotion(false)
{
	m_Velocity = float4::zerovector();
	m_AngularVelocity = float4::zerovector();
}

void hm::MotionComponent::Init()
{
	if (m_Initialized)
		return;

	TransformComponent& t = m_Entity->GetComponent(Type::TRANSFORM);
	m_Transform = &t;

	m_Initialized = true;
}

void hm::MotionComponent::Update()
{
	if (m_InMotion && m_Transform != nullptr) {
		m_Transform->Translate(m_Velocity * hm::Game::deltaTime);
	}

	if (m_InRotation && m_Transform != nullptr) {

		Math::quaternion q = Math::quaternion::rotationyawpitchroll(
			m_AngularVelocity[1] * hm::Game::deltaTime,
			m_AngularVelocity[0] * hm::Game::deltaTime,
			m_AngularVelocity[2] * hm::Game::deltaTime
		);
		m_Transform->Rotate(q);
	}
}

void hm::MotionComponent::Shutdown()
{
}

void hm::MotionComponent::ReceiveMessage(const Message& message)
{
}

void hm::MotionComponent::SetVelocity(const float4& vector)
{
	m_Velocity = vector;
	m_InMotion = (m_Velocity[0] != 0.0f || m_Velocity[1] != 0.0f || m_Velocity[2] != 0.0f);
}

void hm::MotionComponent::SetAngularVelocity(const float4& rotation)
{
	m_AngularVelocity = rotation;
	m_InRotation = (m_AngularVelocity[0] != 0.0f || m_AngularVelocity[1] != 0.0f || m_AngularVelocity[2] != 0.0f);
}

void hm::MotionComponent::ModifyVelocity(const float4& vector)
{
	m_Velocity += vector;
	m_InMotion = (m_Velocity[0] != 0.0f || m_Velocity[1] != 0.0f || m_Velocity[2] != 0.0f);
}

void hm::MotionComponent::ModifyAngularVelocity(const float4& rotation)
{
	m_AngularVelocity += rotation;
	m_InRotation = (m_AngularVelocity[0] != 0.0f || m_AngularVelocity[1] != 0.0f || m_AngularVelocity[2] != 0.0f);
}

void hm::MotionComponent::Serialize(Serializer& writer)
{
	writer.AddNode("motion");
	writer.AddData("velocity", m_Velocity);
	writer.AddData("angular_velocity", m_AngularVelocity);
	writer.EndNode();
}

void hm::MotionComponent::Deserialize(Serializer& reader)
{
	reader.GetData("velocity", m_Velocity);
	reader.GetData("angular_velocity", m_AngularVelocity);
	m_InMotion = (m_Velocity[0] != 0.0f || m_Velocity[1] != 0.0f || m_Velocity[2] != 0.0f);
	m_InRotation = (m_AngularVelocity.lengthsq() != 0.0f);
}
