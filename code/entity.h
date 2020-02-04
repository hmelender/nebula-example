#pragma once
#include "core/refcounted.h"
#include "util/array.h"
#include "util/hashtable.h"
#include "util/variant.h"
#include "util/keyvaluepair.h"
#include "util/stringatom.h"
#include "basecomponent.h"

namespace MyApp
{
	using Core::RefCounted;
	using Util::Array;
	using Util::HashTable;
	using Util::Variant;
	using Util::StringAtom;

	class Entity: RefCounted
	{
	private:

		Array<BaseComponent> m_Components;
		HashTable<StringAtom, Variant> m_Variables;

	public:
		Entity();
		void Init();
		void Update();
		void Shutdown();
	private:

	};
}