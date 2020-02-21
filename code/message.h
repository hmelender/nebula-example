#pragma once
#include "util/queue.h"
#include "util/array.h"
#include "variant_ext.h"
#include "component.h"

namespace hm
{
	using Util::Queue;
	using Util::Array;

	class IMessageHandler;
	class Message;

	class MessageDispatcher
	{
	protected:
		MessageDispatcher();
		void DispatchMessages();

	private:
		static MessageDispatcher* s_Instance;
		Queue<Message> m_MessageQueue;
		Array<IMessageHandler*> m_Handlers;

	public:
		static void RegisterMessageHandler(IMessageHandler& messageHandler);
		static void DeliverMessage(const Message& message);
	};

	class Message
	{
	public:
		enum class Type {
			NONE = 0x0,
			DEFAULT = 0x1,
			SET_ACTIVE = 0x2,
			TRANSFORM = 0x4,
			DESTROY = 0x8,
			DEFAULT4 = 0x10,
			DEFAULT5 = 0x20,
			DEFAULT6 = 0x40,
			DEFAULT7 = 0x80
		};

		friend uint32_t operator|(Type lhs, Type rhs) { return (uint32_t)lhs | (uint32_t)rhs; };
		friend uint32_t operator|(Type lhs, uint32_t rhs) { return (uint32_t)lhs | rhs; };

		Type m_MessageType;
		IMessageHandler* m_Recipient;
		Component::Type m_ComponentType;
		Variant m_MessageData;

		Message();
		Message(Type messageType);
		Message(IMessageHandler& recipient, Type messageType);

	};

	class IMessageHandler
	{
		friend class MessageDispatcher;
	public:
		union MessageTypeFlags {
			struct {
				uint32_t RESERVED0 : 1;
				uint32_t DEFAULT : 1;
				uint32_t SET_ACTIVE : 1;
				uint32_t TRANSFORM : 1;
				uint32_t DESTROY : 1;
				uint32_t RESERVED1 : 27;
				
			};

			uint32_t field;
			MessageTypeFlags() = default;
			MessageTypeFlags(uint32_t i) : field(i) {};
			MessageTypeFlags(Message::Type messageType) : field((uint32_t)messageType) {};
			MessageTypeFlags& operator=(Message::Type& messageType) { this->field = (uint32_t)messageType; return *this; };
		};
	protected:
		MessageTypeFlags m_MessageTypeFlags;
		
		IMessageHandler();

	public:
		virtual void ReceiveMessage(const Message& message) = 0;
		void DeliverMessage(const Message& message) const;
		void RegisterMessageHandler();
		void SubscribeToMsgTypes(MessageTypeFlags messageTypes);
		void UnsubscribeToMsgTypes(MessageTypeFlags messageTypes);
		bool IsSubscribedToMsgType(Message::Type messageType) const;
	};

}
