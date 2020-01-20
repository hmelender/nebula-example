#pragma once
#include "stdneb.h"
#include "graphics/graphicsserver.h"
#include "graphics/graphicsentity.h"
#include "models/model.h"
#include "models/modelcontext.h"
#include "visibility/visibilitycontext.h"
#include "core/refcounted.h"
#include "util/stringatom.h"
#include "resources/resourceid.h"
#include "util/hashtable.h"
#include "ids/idpool.h"

#include "gameentity.h"

namespace Game {

	using Util::StringAtom;
	using Util::HashTable;
	using Models::ModelContext;
	using Visibility::ObservableContext;
	using Visibility::VisibilityEntityType;
	using Ids::IdPool;

	class Entity
	{
	private:
		static IdPool s_IdPool;
		static HashTable<GameEntityId, Entity*> s_Entities;

		GameEntityId m_Id;
		Graphics::GraphicsEntityId m_GraphicsId;
		Math::matrix44 m_Transform;

		bool m_Enabled;


	public:
		GameEntityId& id;

	private:
		virtual void Update();
		Entity(GameEntityId id);
	public:
		static GameEntityId& Create(const Math::point& position);
		static Entity& Get(GameEntityId& id);
		static void UpdateAll();

		virtual ~Entity();
		void LoadModel(const Resources::ResourceName& uri, const StringAtom& tag);
		void SetActive(BOOL enabled);
		void Destroy();

	};

}

