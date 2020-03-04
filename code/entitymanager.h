#pragma once
#include "entity.h"
#include "stdneb.h"
#include "math/point.h"
#include "util/stringatom.h"
#include "message.h"
#include "serializer.h"

namespace hm
{
	class MessageDispatcher;

	class EntityManager: public MessageDispatcher
	{
	private:
		static EntityManager* s_Instance;
		Array<Entity*> m_Entities;
		HashTable<StringAtom, IndexT> m_EntityTable;
		bool m_Initialized;

		Serializer m_Serializer;
	protected:
		EntityManager();
	public:
		static EntityManager& GetInstance();
		Entity& CreateEntity(const StringAtom& name);
		Entity& CreateEntity(const StringAtom& name, const StringAtom& uri, const StringAtom& tag);
		Entity& CreateEntity(const StringAtom& name, const StringAtom& uri, const StringAtom& tag, const Math::point& position);
		Entity& CreatePointLight(const StringAtom& name, const Math::float4& color, float intensity, const Math::point& position, float range, bool castShadows);
		Entity& GetEntity(const StringAtom& name);
		void RemoveEntity(const StringAtom& name);
		void RemoveEntity(Entity& entity);

		void SaveSceneState(const char* file);
		void LoadSceneState(const char* file);
		void Init();
		void Update();
		void Shutdown();

	private:

	};
}
