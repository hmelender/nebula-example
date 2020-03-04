#pragma once
#include "stdneb.h"
#include "core/refcounted.h"
#include "util/array.h"
#include "util/hashtable.h"
#include "variant_ext.h"
#include "util/keyvaluepair.h"
#include "util/stringatom.h"
#include "math/matrix44.h"
#include "math/float4.h"
#include "component.h"
#include "message.h"
#include "serializer.h"

namespace hm
{
	using Core::RefCounted;
	using Util::Array;
	using Util::HashTable;
	using Util::StringAtom;
	using Math::matrix44;
	using Math::float4;

	class Entity: public RefCounted, public IMessageHandler, public ISerializable
	{
		friend class EntityManager;
		__DeclareClass(hm::Entity);
	protected:

		StringAtom m_Name;
		Array<Component*> m_Components;
		HashTable<StringAtom, IndexT> m_ComponentTable;
		HashTable<StringAtom, Variant> m_Variables;
		bool m_Initialized;

	public:
		Entity();
		void Init();
		void Update();
		void Shutdown();

		Component& CreateComponent(Component::Type type);
		Component& GetComponent(Component::Type type);
		Component& GetComponent(const StringAtom& name);
		

		bool RegisterVariable(const StringAtom& name, Variant value)
		{
			if (m_Variables.Contains(name))
				return false;
			m_Variables.Add(name, value);
				return true;
		};

		inline Variant& GetVariable(const StringAtom& name) {
			return m_Variables[name];
		};

		template <typename T>
		inline void SetVariable(const StringAtom& name, T& value) {
			m_Variables[name] = value;
		};

		void ReceiveMessage(const hm::Message& message);

		void Serialize(Serializer& writer);
		void Deserialize(Serializer& reader);

	};
}