#include "graphicscomponent.h"
#include "transformcomponent.h"

MyApp::GraphicsComponent::GraphicsComponent()
{
}

void MyApp::GraphicsComponent::Init()
{
	m_GraphicsId = Graphics::CreateEntity();
	m_Entity->RegisterVariable("graphics_id", m_GraphicsId);
}

void MyApp::GraphicsComponent::Update()
{
}

void MyApp::GraphicsComponent::Shutdown()
{
}

void MyApp::GraphicsComponent::ReceiveMessage(const Message& message)
{
}

void MyApp::GraphicsComponent::LoadModel(const Resources::ResourceName& uri, const StringAtom& tag)
{
	const matrix44& t = m_Entity->GetVariable<matrix44>("transform_matrix");
	ModelContext::Setup(m_GraphicsId, uri, tag);
	ModelContext::SetTransform(m_GraphicsId, t);
	ObservableContext::Setup(m_GraphicsId, VisibilityEntityType::Model);
}
