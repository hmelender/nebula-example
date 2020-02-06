#pragma once
#include "stdneb.h"
#include "math/matrix44.h"
#include "math/quaternion.h"
#include "component.h"

namespace MyApp
{
	using Math::matrix44;
	using Math::quaternion;

	class TransformComponent : Component
	{
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
	};

}

