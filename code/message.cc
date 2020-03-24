#include "message.h"

hm::MessageDispatcher* hm::MessageDispatcher::s_Instance = nullptr;

hm::IMessageHandler::IMessageHandler() : m_MessageTypeFlags((uint32_t)0)
{}

void hm::IMessageHandler::DeliverMessage(const Message& message) const
{
	MessageDispatcher::DeliverMessage(message);
}

void hm::IMessageHandler::RegisterMessageHandler()
{
	MessageDispatcher::RegisterMessageHandler(*this);
}

void hm::IMessageHandler::SubscribeToMsgTypes(hm::IMessageHandler::MessageTypeFlags messageTypes)
{
	m_MessageTypeFlags.field |= (uint32_t)messageTypes.field;
}

void hm::IMessageHandler::UnsubscribeToMsgTypes(hm::IMessageHandler::MessageTypeFlags messageTypes)
{
	m_MessageTypeFlags.field |= ~((uint32_t)messageTypes.field);
}

bool hm::IMessageHandler::IsSubscribedToMsgType(Message::Type messageType) const
{
	return m_MessageTypeFlags.field & (uint32_t)messageType;
}

hm::MessageDispatcher::MessageDispatcher()
{
	if (s_Instance != nullptr)
		throw std::exception("MessageDispatcher already implemented!");

	s_Instance = this;
}

void hm::MessageDispatcher::RegisterMessageHandler(IMessageHandler& messageHandler)
{
	if (s_Instance == nullptr)
		throw std::exception("MessageDispatcher not implemented!");

	if (s_Instance->m_Handlers.FindIndex(&messageHandler) != InvalidIndex)
		throw std::exception("MessageHandler already registered!");

	s_Instance->m_Handlers.Append(&messageHandler);
}

void hm::MessageDispatcher::DeliverMessage(const Message& message)
{
	if (s_Instance == nullptr)
		throw std::exception("MessageDispatcher not implemented!");

	s_Instance->m_MessageQueue.Enqueue(message);
}


void hm::MessageDispatcher::DispatchMessages()
{
	if (m_MessageQueue.IsEmpty())
		return;

	Message& msg = m_MessageQueue.Dequeue();
	IMessageHandler* handler = msg.m_Recipient;

	if (msg.m_Recipient == nullptr) { // Send to all
		for (IMessageHandler* h : m_Handlers) {
			if (h->m_MessageTypeFlags.field & (uint32_t)msg.m_MessageType) {
				msg.m_Recipient->ReceiveMessage(msg);
			}
		}
	}
	else if (msg.m_Recipient->m_MessageTypeFlags.field & (uint32_t)msg.m_MessageType) {
		msg.m_Recipient->ReceiveMessage(msg);
	}
	
}

void hm::MessageDispatcher::ClearMessageHandlers()
{
	m_Handlers.Clear();
}

void hm::MessageDispatcher::ClearMessageQueue()
{
	m_MessageQueue.Clear();
}

hm::Message::Message() : m_MessageType(hm::Message::Type::NONE), m_Recipient(nullptr)
{}

hm::Message::Message(Type messageType) : m_MessageType(messageType), m_Recipient(nullptr)
{}

hm::Message::Message(IMessageHandler& recipient, Type messageType) : m_MessageType(messageType), m_Recipient(&recipient)
{}
