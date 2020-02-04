#pragma once
#include "core/refcounted.h"

namespace MyApp {

	using Core::RefCounted;

	class BaseComponent: RefCounted
	{
	private:

	public:
		BaseComponent();
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;


	private:

	};

}