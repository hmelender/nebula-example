#pragma once

namespace Game
{
	class IMessageHandler
	{
	public:
		virtual void ReceiveMessage(const Message& message) = 0;
	};

	class Message
	{

	};



}