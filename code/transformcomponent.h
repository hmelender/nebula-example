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

	class TransformComponent : public Component, public RefCounted, public ISerializable
	{
		__DeclareClass(hm::TransformComponent);
		friend class GraphicsComponent;
		friend class LightComponent;
	protected:

		point m_Position;
		float4 m_Scale;
		quaternion m_Rotation;

		point m_Pivot;
		matrix44 m_Matrix;
		Component* m_Transformable;

		bool m_UpdateMatrix;
	public:
		enum class Axis
		{
			X, Y, Z
		};

		TransformComponent();

		void Init();
		void Update();
		void Shutdown();
		void ReceiveMessage(const Message& message);

		void SetPosition(const point& position);
		void SetPosition(float x, float y, float z);
		void Translate(const float4& vector);
		void Translate(float x, float y, float z);
		void SetRotation(const quaternion& rotation);
		void Rotate(const quaternion& rotation);
		void SetRotationEuler(float x, float y, float z);
		void RotateAxis(const float4& axis, float angle);
		void RotateAxis(Axis axis, float angle);
		void SetScale(float scale);
		void SetScale(const float4& scale);
		void SetScale(float x, float y, float z);
		void SetPivot(const point& position);

		void Serialize(Serializer& writer) override;
		void Deserialize(Serializer& reader) override;
	};

}

