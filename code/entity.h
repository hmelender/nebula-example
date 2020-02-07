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

namespace MyApp
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
	private:

		Array<Component> m_Components;
		HashTable<StringAtom, Variant> m_Variables;

	public:
		Entity();
		void Init();
		void Update();
		void Shutdown();

		void AddComponent(Component& component);
		void CreateComponent(Component::Type componentType);

		template <typename T>
		bool RegisterVariable(const StringAtom& name, T& value) {
			if (m_Variables.Contains(name))
				return false;

			m_Variables.Add(name, Variant(value));
			return true;
		};

		template <typename T>
		inline T& GetVariable(const StringAtom& name) {
			return m_Variables[name].Get();
		};

		template <typename T>
		inline void SetVariable(const StringAtom& name, T& value) {
			m_Variables[name] = value;
		};

		void ReceiveMessage(const Message& message);

	private:

	};
}