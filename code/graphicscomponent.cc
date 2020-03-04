#include "graphicscomponent.h"
#include "transformcomponent.h"
#include "entity.h"
#include "message.h"

namespace hm
{
	__ImplementClass(hm::GraphicsComponent, 'HMGC', Core::RefCounted)
}

void hm::GraphicsComponent::SetTransform(const Math::matrix44& matrix)
{
	ModelContext::SetTransform(m_GraphicsId, matrix);
}

hm::GraphicsComponent::GraphicsComponent() : hm::Component(Type::GRAPHICS)
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
	Graphics::DeregisterEntity<ModelContext, ObservableContext>(m_GraphicsId);
	Graphics::DestroyEntity(m_GraphicsId);
}

void hm::GraphicsComponent::ReceiveMessage(const Message& message)
{
}

hm::GraphicsComponent& hm::GraphicsComponent::operator=(const hm::Component& rhs)
{
	return *(GraphicsComponent*)(&rhs);
}

void hm::GraphicsComponent::LoadModel(const StringAtom& uri, const StringAtom& tag)
{
	TransformComponent& t = m_Entity->GetComponent(Type::TRANSFORM);
	t.m_Transformable = this;

	m_ModelUri = uri;
	m_ModelTag = tag;
	ModelContext::Setup(m_GraphicsId, m_ModelUri, m_ModelTag);
	ModelContext::SetTransform(m_GraphicsId, t.m_Matrix);
	ObservableContext::Setup(m_GraphicsId, VisibilityEntityType::Model);

}

void hm::GraphicsComponent::ChangeModel(const StringAtom& uri, const StringAtom& tag)
{
	m_ModelUri = uri;
	m_ModelTag = tag;
	ModelContext::ChangeModel(m_GraphicsId, m_ModelUri, m_ModelTag);
}

void hm::GraphicsComponent::Serialize(Serializer& writer)
{
	writer.AddNode("graphics");
	writer.AddData("model_uri", m_ModelUri);
	writer.AddData("model_tag", m_ModelTag);
	writer.EndNode();
}

void hm::GraphicsComponent::Deserialize(Serializer& reader)
{
	StringAtom uri;
	StringAtom tag;
	reader.GetData("model_uri", uri);
	reader.GetData("model_tag", tag);
	LoadModel(uri, tag);
	m_Initialized = false;
	Init();
}
