#include "graphicscomponent.h"
#include "transformcomponent.h"
#include "entity.h"

namespace hm
{
	__ImplementClass(hm::GraphicsComponent, 'HMGC', Core::RefCounted)
}

void hm::GraphicsComponent::SetTransform(const Math::matrix44& matrix)
{
	ModelContext::SetTransform(m_GraphicsId, matrix);
}

hm::GraphicsComponent::GraphicsComponent() : hm::Component()
{
}

void hm::GraphicsComponent::Init()
{
	if (m_Initialized)
		return;
	
	m_GraphicsId = Graphics::CreateEntity();
	Graphics::RegisterEntity<ModelContext, ObservableContext>(m_GraphicsId);
	m_Initialized = true;
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

hm::GraphicsComponent& hm::GraphicsComponent::operator=(const hm::Component& rhs)
{
	return *(GraphicsComponent*)(&rhs);
}

void hm::GraphicsComponent::LoadModel(const Resources::ResourceName& uri, const StringAtom& tag)
{
	TransformComponent& t = m_Entity->GetComponent("transform");
	t.m_Graphics = this;

	ModelContext::Setup(m_GraphicsId, uri, tag);
	ModelContext::SetTransform(m_GraphicsId, *(t.m_Matrix));
	ObservableContext::Setup(m_GraphicsId, VisibilityEntityType::Model);

}

void hm::GraphicsComponent::ChangeModel(const Resources::ResourceName& uri, const StringAtom& tag)
{
	ModelContext::ChangeModel(m_GraphicsId, uri, tag);
}
