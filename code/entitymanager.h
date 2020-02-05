#pragma once
#include "entity.h"

namespace MyApp
{
	class EntityManager
	{
	private:
		static EntityManager* s_Instance;
		EntityManager();
	public:
		static EntityManager& GetInstance();
		Entity& CreateEntity();
		void Init();
		void Update();
		void Shutdown();

	private:

	};
}
