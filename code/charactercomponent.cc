#include "charactercomponent.h"
#include "graphicscomponent.h"
#include "transformcomponent.h"
#include "entity.h"
#include "message.h"

namespace hm
{
	__ImplementClass(hm::CharacterComponent, 'HMCC', Core::RefCounted)
}

hm::CharacterComponent::CharacterComponent() : hm::Component(Type::CHARACTER)
{
}

void hm::CharacterComponent::Init()
{
	if (m_Initialized)
		return;
	
	m_Initialized = true;
}

void hm::CharacterComponent::Update()
{
}

void hm::CharacterComponent::Shutdown()
{
	Characters::CharacterContext::DeregisterEntity(m_GraphicsId);
}

void hm::CharacterComponent::ReceiveMessage(const Message& message)
{
}

hm::CharacterComponent& hm::CharacterComponent::operator=(const hm::Component& rhs)
{
	return *(CharacterComponent*)(&rhs);
}

void hm::CharacterComponent::LoadCharacter(const StringAtom& skeletonUri, const StringAtom& animationUri, const StringAtom& tag)
{
	GraphicsComponent& g = m_Entity->GetComponent(Component::Type::GRAPHICS);
	m_GraphicsId = g.m_GraphicsId;
	Characters::CharacterContext::RegisterEntity(m_GraphicsId);
	Characters::CharacterContext::Setup(m_GraphicsId, skeletonUri, animationUri, tag);

	m_SkeletonUri = skeletonUri;
	m_AnimationUri = animationUri;
	m_CharacterTag = tag;

}

void hm::CharacterComponent::PlayAnimation(const IndexT clipIndex, const IndexT track, const Characters::EnqueueMode mode, const float weight, const SizeT loopCount, const float startTime, const float fadeIn, const float fadeOut, const float timeOffset, const float timeFactor)
{
	Characters::CharacterContext::PlayClip(m_GraphicsId, nullptr, clipIndex, track, mode, weight, loopCount, startTime, fadeIn, fadeOut, timeOffset, timeFactor);
	m_AnimPlaying = true;
}


void hm::CharacterComponent::Serialize(Serializer& writer)
{
	writer.AddNode("character");
	writer.AddData("skeleton_uri", m_SkeletonUri);
	writer.AddData("animation_uri", m_AnimationUri);
	writer.AddData("character_tag", m_CharacterTag);
	writer.AddData("anim_playing", m_AnimPlaying);
	writer.EndNode();
}

void hm::CharacterComponent::Deserialize(Serializer& reader)
{
	StringAtom skUri;
	StringAtom anUri;
	StringAtom tag;
	reader.GetData("skeleton_uri", skUri);
	reader.GetData("animation_uri", anUri);
	reader.GetData("character_tag", tag);
	reader.GetData("anim_playing", m_AnimPlaying);
	LoadCharacter(skUri, anUri, tag);
	if (m_AnimPlaying) {
		// PlayAnimation()
	}
}
