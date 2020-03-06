#pragma once
#include "stdneb.h"
#include "core/refcounted.h"
#include "math/transform44.h"
#include "math/matrix44.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/quaternion.h"
#include "component.h"

namespace hm
{
	using Math::transform44;
	using Math::matrix44;
	using Math::float4;
	using Math::point;
	using Math::vector;
	using Math::quaternion;
	using Core::RefCounted;

	class MotionComponent : public Component, public RefCounted, public ISerializable
	{
		__DeclareClass(hm::MotionComponent);
		friend class GraphicsComponent;
		friend class LightComponent;
	protected:

		float4 m_Velocity;
		float4 m_AngularVelocity;

		bool m_InMotion;
		bool m_InRotation;
		TransformComponent* m_Transform;

	public:

		MotionComponent();

		void Init();
		void Update();
		void Shutdown();
		void ReceiveMessage(const Message& message);

		void SetVelocity(const float4& vector);
		void SetAngularVelocity(const float4& rotation);
		void ModifyVelocity(const float4& vector);
		void ModifyAngularVelocity(const float4& rotation);

		void Serialize(Serializer& writer) override;
		void Deserialize(Serializer& reader) override;
	};

}

