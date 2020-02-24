#pragma once
#include "stdneb.h"

namespace hm
{
	class Entity;
	class TransformComponent;
	class GraphicsComponent;
	class LightComponent;
	class Message;

	class Component
	{
		friend class Entity;
	protected:
		Entity* m_Entity;
		bool m_Initialized;
	public:
		enum class Type {
			NONE, TRANSFORM, GRAPHICS, LIGHT, CHARACTER
		};
		const Type m_Type;

		Component(Type type);
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;
		virtual void ReceiveMessage(const Message& message) = 0;
		virtual void SetTransform(const Math::matrix44& matrix);

		operator hm::TransformComponent&();
		operator hm::GraphicsComponent& ();
		operator hm::LightComponent& ();

	private:

	};

}
