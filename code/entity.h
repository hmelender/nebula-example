#pragma once
#include "stdneb.h"
#include "core/refcounted.h"
#include "util/array.h"
#include "util/hashtable.h"
#include "util/variant.h"
#include "util/keyvaluepair.h"
#include "util/stringatom.h"
#include "math/matrix44.h"
#include "math/float4.h"
#include "component.h"
#include "message.h"

namespace hm
{
	using Core::RefCounted;
	using Util::Array;
	using Util::HashTable;
	using Util::Variant;
	using Util::StringAtom;
	using Math::matrix44;
	using Math::float4;

	class Entity: public RefCounted, public IMessageHandler
	{
		__DeclareClass(hm::Entity);
	private:

		Array<Component*> m_Components;
		HashTable<StringAtom, IndexT> m_ComponentTable;
		HashTable<StringAtom, Variant> m_Variables;

	public:
		Entity();
		void Init();
		void Update();
		void Shutdown();

		Component& CreateComponent(Component::Type componentType);
		Component& GetComponent(const StringAtom& name);

		bool RegisterVariable(const StringAtom& name, Variant& value);

		inline Variant& GetVariable(const StringAtom& name) {
			return m_Variables[name];
		};

		inline void SetVariable(const StringAtom& name, Variant& value) {
			m_Variables[name] = value;
		};

		void ReceiveMessage(const hm::Message& message);

	private:

	};
}