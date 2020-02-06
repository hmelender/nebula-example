#pragma once

namespace MyApp
{

	class Message
	{
	private:
		
	public:
		enum Type {
			DEFAULT
		};

		Message();

	};

	class IMessageHandler
	{
	public:
		virtual void ReceiveMessage(const Message& message) = 0;
	};




}