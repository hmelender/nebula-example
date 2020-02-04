#pragma once

namespace MyApp
{
	class EntityManager
	{
	private:
		static EntityManager* s_Instance;
		EntityManager();
	public:
		static EntityManager& GetInstance();
	private:

	};
}
