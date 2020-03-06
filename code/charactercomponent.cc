#include "charactercomponent.h"
#include "graphicscomponent.h"
#include "transformcomponent.h"
#include "entity.h"
#include "message.h"

namespace hm
{
	__ImplementClass(hm::CharacterComponent, 'HMCC', Core::RefCounted)
}

hm::CharacterComponent::CharacterComponent() : hm::Component(Type::CHARACTER), m_AnimPlaying(false),
	m_ClipIndex(0),
	m_Track(0),
	m_Mode(Characters::EnqueueMode::Append),
	m_Weight(1.0f),
	m_LoopCount(1),
	m_StartTime(0.0f),
	m_FadeIn(0.0f),
	m_FadeOut(0.0f),
	m_TimeOffset(0.0f),
	m_TimeFactor(1.0f)
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
	m_ClipIndex = clipIndex;
	m_Track = track;
	m_Mode = mode;
	m_Weight = weight;
	m_LoopCount = loopCount;
	m_StartTime = startTime;
	m_FadeIn = fadeIn;
	m_FadeOut = fadeOut;
	m_TimeOffset = timeOffset;
	m_TimeFactor = timeFactor;
}


void hm::CharacterComponent::Serialize(Serializer& writer)
{
	writer.AddNode("character");
	writer.AddData("skeleton_uri", m_SkeletonUri);
	writer.AddData("animation_uri", m_AnimationUri);
	writer.AddData("character_tag", m_CharacterTag);
	writer.AddData("anim_playing", m_AnimPlaying);

	if (m_AnimPlaying) {
		writer.AddData("clip_index", m_ClipIndex);
		writer.AddData("track", m_Track);
		int mode = m_Mode;
		writer.AddData("mode", mode);
		writer.AddData("weight", m_Weight);
		writer.AddData("loop_count", m_LoopCount);
		writer.AddData("start_time", m_StartTime);
		writer.AddData("fade_in", m_FadeIn);
		writer.AddData("fade_out", m_FadeOut);
		writer.AddData("time_offset", m_TimeOffset);
		writer.AddData("time_factor", m_TimeFactor);
	}

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

	LoadCharacter(skUri, anUri, tag);

	reader.GetData("anim_playing", m_AnimPlaying);

	if (m_AnimPlaying) {
		IndexT clipIndex = 0;
		IndexT track = 0;
		int mode = 0;
		float weight = 0.0f;
		SizeT loopCount = 1;
		float startTime = 0.0f;
		float fadeIn = 0.0f;
		float fadeOut = 0.0f;
		float timeOffset = 0.0f;
		float timeFactor = 1.0f;

		reader.GetData("clip_index", clipIndex);
		reader.GetData("track", track);

		reader.GetData("mode", mode);
		m_Mode = static_cast<Characters::EnqueueMode>(mode);
		reader.GetData("weight", weight);
		reader.GetData("loop_count", loopCount);
		reader.GetData("start_time", startTime);
		reader.GetData("fade_in", fadeIn);
		reader.GetData("fade_out", fadeOut);
		reader.GetData("time_offset", timeOffset);
		reader.GetData("time_factor", timeFactor);

		PlayAnimation(clipIndex, track, static_cast<Characters::EnqueueMode>(mode), weight, loopCount, startTime, fadeIn, fadeOut, timeOffset, timeFactor);
	}

}
