#include "transformcomponent.h"

MyApp::TransformComponent::TransformComponent()
{
}

void MyApp::TransformComponent::Init()
{
	m_Position = float4::zerovector();
	m_Velocity = float4::zerovector();
	m_Scale = float4(1.0f, 1.0f, 1.0, 1.0);
	m_Rotation = quaternion::identity();

	m_Matrix = matrix44::identity();
	m_Entity->RegisterVariable("transform_matrix", m_Matrix);
}

void MyApp::TransformComponent::Update()
{
}

void MyApp::TransformComponent::Shutdown()
{
}
