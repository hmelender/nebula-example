#pragma once

namespace MyApp
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