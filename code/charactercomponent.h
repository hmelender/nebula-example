#pragma once
#include "stdneb.h"
#include "core/refcounted.h"
#include "util/stringatom.h"
#include "graphics/graphicsserver.h"
#include "graphics/graphicsentity.h"
#include "models/model.h"
#include "models/modelcontext.h"
#include "characters/charactercontext.h"
#include "visibility/visibilitycontext.h"
#include "component.h"
#include "math/matrix44.h"

namespace hm
{
	using Graphics::GraphicsEntityId;
	using Models::ModelContext;
	using Visibility::ObservableContext;
	using Visibility::VisibilityEntityType;
	using Util::StringAtom;
	using Core::RefCounted;

	class CharacterComponent : public Component, public RefCounted, public ISerializable
	{
		__DeclareClass(hm::CharacterComponent);
		friend class TransformComponent;
	protected:
		GraphicsEntityId m_GraphicsId;
		StringAtom m_SkeletonUri;
		StringAtom m_AnimationUri;
		StringAtom m_CharacterTag;
		bool m_AnimPlaying;

		IndexT m_ClipIndex;
		IndexT m_Track;
		Characters::EnqueueMode m_Mode;
		float m_Weight;
		SizeT m_LoopCount;
		float m_StartTime;
		float m_FadeIn;
		float m_FadeOut;
		float m_TimeOffset;
		float m_TimeFactor;

	public:
		CharacterComponent();
		void Init();
		void Update();
		void Shutdown();
		void ReceiveMessage(const Message& message);

		CharacterComponent& operator=(const Component& rhs);

		void LoadCharacter(const StringAtom& skeletonUri, const StringAtom& animationUri, const StringAtom& tag);
		void PlayAnimation(
			const IndexT clipIndex,
			const IndexT track,
			const Characters::EnqueueMode mode,
			const float weight = 1.0f,
			const SizeT loopCount = 1,
			const float startTime = 0.0f,
			const float fadeIn = 0.0f,
			const float fadeOut = 0.0f,
			const float timeOffset = 0.0f,
			const float timeFactor = 1.0f
		);

		void Serialize(Serializer& writer) override;
		void Deserialize(Serializer& reader) override;
	};

}

