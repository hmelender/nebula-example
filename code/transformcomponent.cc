#include "transformcomponent.h"

MyApp::TransformComponent::TransformComponent()
{
}

void MyApp::TransformComponent::Init()
{
	m_Matrix = matrix44::identity();
	m_Entity->RegisterVariable("transform_matrix", m_Matrix);
}

void MyApp::TransformComponent::Update()
{
}

void MyApp::TransformComponent::Shutdown()
{
}
