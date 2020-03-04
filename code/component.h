#pragma once
#include "stdneb.h"
#include "serializer.h"

namespace hm
{
	class Entity;
	class TransformComponent;
	class GraphicsComponent;
	class LightComponent;
	class CharacterComponent;
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
		virtual void Serialize(Serializer& writer) = 0;
		virtual void Deserialize(Serializer& reader) = 0;
		virtual void SetTransform(const Math::matrix44& matrix);

		operator hm::TransformComponent&();
		operator hm::GraphicsComponent&();
		operator hm::LightComponent&();
		operator hm::CharacterComponent&();

		static Type TypeFromString(const char* str) {
			std::string strn(str);
			for (char& c : strn) {
				c = toupper(c);
			}

			if		(strn.compare("TRANSFORM") == 0)	return Type::TRANSFORM;
			else if (strn.compare("GRAPHICS") == 0)		return Type::GRAPHICS;
			else if (strn.compare("LIGHT") == 0)		return Type::LIGHT;
			else if (strn.compare("CHARACTER") == 0)	return Type::CHARACTER;
			else										return Type::NONE;
		};

	private:

	};

}
