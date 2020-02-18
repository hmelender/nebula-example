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

		template <typename T>
		T& CreateComponent(Component::Type componentType)
		{
			Component* c = nullptr;
			switch (componentType)
			{
			case hm::Component::TRANSFORM:
				c = TransformComponent::Create(); break;
				m_ComponentTable.Add("transform", m_Components.Size());
			case hm::Component::GRAPHICS:
				c = GraphicsComponent::Create(); break;
				m_ComponentTable.Add("graphics", m_Components.Size());
			default: return;
			}

			c->m_Entity = this;
			m_Components.Append(c);

			switch (componentType)
			{
			case hm::Component::TRANSFORM:
				return *(TransformComponent*)c;
			case hm::Component::GRAPHICS:
				return *(GraphicsComponent*)c;
			default: return;
			}
		
		}

		Component& GetComponent(const StringAtom& name);

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