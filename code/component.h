#pragma once
#include "stdneb.h"

namespace hm
{
	class Entity;
	class TransformComponent;
	class GraphicsComponent;
	class Message;

	class Component
	{
		friend class Entity;
	protected:
		Entity* m_Entity;
		bool m_Initialized;
	public:
		enum class Type {
			NONE, TRANSFORM, GRAPHICS, CHARACTER
		};

		Component();
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;
		virtual void ReceiveMessage(const Message& message) = 0;

		operator hm::TransformComponent&();

	private:

	};

}
