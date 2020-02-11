#pragma once
#include "stdneb.h"
#include "graphics/graphicsserver.h"
#include "graphics/graphicsentity.h"
#include "models/model.h"
#include "models/modelcontext.h"
#include "visibility/visibilitycontext.h"
#include "component.h"

namespace hm
{
	using Graphics::GraphicsEntityId;
	using Models::ModelContext;
	using Visibility::ObservableContext;
	using Visibility::VisibilityEntityType;

	class GraphicsComponent : public Component
	{
	private:
		GraphicsEntityId m_GraphicsId;

	public:
		GraphicsComponent();
		void Init();
		void Update();
		void Shutdown();
		void ReceiveMessage(const Message& message);
		void LoadModel(const Resources::ResourceName& uri, const StringAtom& tag);
	};

}

