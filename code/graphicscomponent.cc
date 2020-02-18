#include "graphicscomponent.h"
#include "transformcomponent.h"

namespace hm
{
	__ImplementClass(hm::GraphicsComponent, 'HMGC', Core::RefCounted)
}

hm::GraphicsComponent::GraphicsComponent()
{
}

void hm::GraphicsComponent::Init()
{
	m_GraphicsId = Graphics::CreateEntity();
	m_Entity->RegisterVariable("graphics_id", m_GraphicsId);
}

void hm::GraphicsComponent::Update()
{
}

void hm::GraphicsComponent::Shutdown()
{
}

void hm::GraphicsComponent::ReceiveMessage(const Message& message)
{
}

void hm::GraphicsComponent::LoadModel(const Resources::ResourceName& uri, const StringAtom& tag)
{
	const matrix44& t = m_Entity->GetVariable<matrix44>("transform_matrix");
	ModelContext::Setup(m_GraphicsId, uri, tag);
	ModelContext::SetTransform(m_GraphicsId, t);
	ObservableContext::Setup(m_GraphicsId, VisibilityEntityType::Model);
}
