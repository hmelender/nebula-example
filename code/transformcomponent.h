#pragma once
#include "stdneb.h"
#include "core/refcounted.h"
#include "math/matrix44.h"
#include "math/float4.h"
#include "math/quaternion.h"
#include "component.h"

namespace hm
{
	using Math::matrix44;
	using Math::float4;
	using Math::quaternion;
	using Core::RefCounted;

	class TransformComponent : public Component, public RefCounted
	{
		__DeclareClass(hm::TransformComponent);
	private:
		float4 m_Velocity;

		float4 m_Position;
		float4 m_Scale;
		quaternion m_Rotation;

		matrix44 m_Matrix;
	public:
		TransformComponent();
		void Init();
		void Update();
		void Shutdown();
		void ReceiveMessage(const Message& message);
	};

}

