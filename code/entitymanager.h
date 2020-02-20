#pragma once
#include "entity.h"
#include "stdneb.h"
#include "math/point.h"
#include "util/stringatom.h"
#include "message.h"

namespace hm
{
	class EntityManager: public MessageDispatcher
	{
	private:
		static EntityManager* s_Instance;
		Array<Entity*> m_Entities;
		HashTable<StringAtom, IndexT> m_EntityTable;
		bool m_Initialized;
	protected:
		EntityManager();
	public:
		static EntityManager& GetInstance();
		Entity& CreateEntity(const StringAtom& name);
		Entity& CreateEntity(const StringAtom& name, const Resources::ResourceName& uri, const StringAtom& tag);
		Entity& CreateEntity(const StringAtom& name, const Resources::ResourceName& uri, const StringAtom& tag, const Math::point& position);
		Entity& GetEntity(const StringAtom& name);
		void RemoveEntity(const StringAtom& name);
		void Init();
		void Update();
		void Shutdown();

	private:

	};
}
