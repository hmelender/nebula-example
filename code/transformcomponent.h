#pragma once
#include "stdneb.h"
#include "math/matrix44.h"
#include "component.h"

namespace MyApp
{
	using Math::matrix44;

	class TransformComponent : Component
	{
	private:
		matrix44 m_Transform;
	public:
		TransformComponent();
		void Init();
		void Update();
		void Shutdown();
	};

}

