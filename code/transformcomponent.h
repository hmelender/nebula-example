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

	class TransformComponent : public Component, public RefCounted
	{
		__DeclareClass(hm::TransformComponent);
		friend class GraphicsComponent;
	protected:

		float4 m_Velocity;
		transform44 m_Transform;
		const matrix44* m_Matrix;
		GraphicsComponent* m_Graphics;

		bool m_InMotion;
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

		/*
		TransformComponent& operator=(hm::Component& rhs) {
			return *this = dynamic_cast<TransformComponent&>(rhs);
		}
		*/
		/*
		TransformComponent& operator=(Component const& rhs)
		{ return *this = dynamic_cast<TransformComponent const &>(rhs); }
		*/

		void SetPosition(const point& position);
		void SetPosition(float x, float y, float z);
		void Translate(const float4& vector);
		void Translate(float x, float y, float z);
		void SetVelocity(const float4& vector);
		void SetRotation(const quaternion& rotation);
		void SetRotationEuler(float x, float y, float z);
		void RotateAxis(float4 axis, float angle);
		void RotateAxis(Axis axis, float angle);
		void SetScale(float scale);
		void SetScale(const float4& scale);
		void SetScale(float x, float y, float z);
	};

}

