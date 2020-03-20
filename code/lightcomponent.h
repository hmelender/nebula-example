#pragma once
#include "stdneb.h"
#include "core/refcounted.h"
#include "util/stringatom.h"
#include "graphics/graphicsserver.h"
#include "graphics/graphicsentity.h"
#include "models/model.h"
#include "models/modelcontext.h"
#include "lighting/lightcontext.h"
#include "visibility/visibilitycontext.h"
#include "math/matrix44.h"

#include "component.h"


namespace hm
{
	using Graphics::GraphicsEntityId;
	using Models::ModelContext;
	using Visibility::ObservableContext;
	using Visibility::VisibilityEntityType;
	using Util::StringAtom;
	using Core::RefCounted;

	class LightComponent : public Component, public RefCounted, public ISerializable
	{
		__DeclareClass(hm::LightComponent);
		friend class TransformComponent;
	protected:
		GraphicsEntityId m_LightId;
		Math::float4 m_Color;
		float m_Intensity;
		float m_Range;
		bool m_CastShadows;

		void SetTransform(const Math::matrix44& matrix);
	public:
		LightComponent();
		void Init();
		void Update();
		void Shutdown();
		void ReceiveMessage(const Message& message);

		LightComponent& operator=(const Component& rhs);

		void SetupPointLight(const Math::float4& color, float intensity, float range, bool castShadows);

		void Serialize(Serializer& writer) override;
		void Deserialize(Serializer& reader) override;
	};

}

