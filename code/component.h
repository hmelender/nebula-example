#pragma once
#include "stdneb.h"
#include "message.h"

namespace hm
{
	class Entity;
	class TransformComponent;
	class GraphicsComponent;

	class Component: public IMessageHandler
	{
		friend class Entity;
	protected:
		Entity* m_Entity;
		bool m_Initialized;
	public:
		enum class Type {
			TRANSFORM, GRAPHICS, CHARACTER
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
