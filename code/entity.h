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

	class Entity: RefCounted, IMessageHandler
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

		template <typename T>
		bool RegisterVariable(const StringAtom& name, T& value) {
			if (m_Variables.Contains(name))
				return false;

			m_Variables.Add(name, Variant(value));
			return true;
		};

		Variant& GetVariable(const StringAtom& name) {
			return m_Variables[name];
		};

		/*
		template <typename TYPE>
		TYPE& GetVariable(const StringAtom& name) {
			return m_Variables[name].Get();
		};

		template <>
		const matrix44& GetVariable(const StringAtom& name) {
			return m_Variables[name].GetMatrix44();
		};

		template <>
		float4& GetVariable(const StringAtom& name) {
			return m_Variables[name].GetFloat4();
		}
		*/

		template <typename T>
		void SetVariable(const StringAtom& name, T& value) {
			m_Variables[name] = value;
		};

		void ReceiveMessage(const Message& message);

	private:

	};
}