#include "Entity.h"

namespace Game
{
	IdPool Entity::s_IdPool;
	HashTable<GameEntityId, Entity*> Entity::s_Entities;	

	GameEntityId& Game::Entity::Create(const Math::point& position)
	{
		// Allocate unique id
		GameEntityId gId;
		gId.id = s_IdPool.Alloc();
		Entity* e = new Entity(gId);

		s_Entities.Add(gId, e);

		e->m_GraphicsId = Graphics::CreateEntity();
		e->m_Transform = Math::matrix44::translation(position);

		Graphics::RegisterEntity<ModelContext, ObservableContext>(e->m_GraphicsId);

		return e->m_Id;
	}

	Entity& Entity::Get(GameEntityId& id)
	{
		return *s_Entities[id.id];
	}

	Entity::~Entity()
	{
		if (s_Entities.Contains(m_Id))
			s_Entities.Erase(m_Id);

		s_IdPool.Dealloc(m_Id.id);
	}

	void Entity::LoadModel(const Resources::ResourceName& uri, const StringAtom& tag)
	{
		ModelContext::Setup(m_GraphicsId, uri, tag);
		ModelContext::SetTransform(m_GraphicsId, m_Transform);
		ObservableContext::Setup(m_GraphicsId, VisibilityEntityType::Model);
		
	}

	Entity::Entity(GameEntityId id) : m_Id(id), id(m_Id), m_Enabled(true)
	{}

	void Entity::UpdateAll()
	{
		auto it = s_Entities.Begin();
		Entity* e;

		while (e = *it.val) {
			if (e->m_Enabled) {
				e->Update();
			}
			it++;
		}

	}

	void Entity::Update()
	{

	}


	void Entity::SetActive(BOOL enabled)
	{
		if (m_Enabled && !enabled) { // Is this how you disable rendering?
			ObservableContext::DeregisterEntity(m_GraphicsId);
		}
		else if (!m_Enabled && enabled) {
			ObservableContext::RegisterEntity(m_GraphicsId);
		}
		m_Enabled = enabled;
	}

	void Entity::Destroy()
	{
	}
}
