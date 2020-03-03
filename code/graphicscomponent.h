#pragma once
#include "stdneb.h"
#include "core/refcounted.h"
#include "util/stringatom.h"
#include "graphics/graphicsserver.h"
#include "graphics/graphicsentity.h"
#include "models/model.h"
#include "models/modelcontext.h"
#include "visibility/visibilitycontext.h"
#include "component.h"
#include "math/matrix44.h"

namespace hm
{
	using Graphics::GraphicsEntityId;
	using Models::ModelContext;
	using Visibility::ObservableContext;
	using Visibility::VisibilityEntityType;
	using Util::StringAtom;
	using Core::RefCounted;

	class GraphicsComponent : public Component, public RefCounted
	{
		__DeclareClass(hm::GraphicsComponent);
		friend class TransformComponent;
	protected:
		GraphicsEntityId m_GraphicsId;

		void SetTransform(const Math::matrix44& matrix);
	public:
		GraphicsComponent();
		void Init();
		void Update();
		void Shutdown();
		void ReceiveMessage(const Message& message);

		GraphicsComponent& operator=(const Component& rhs);

		void LoadModel(const StringAtom& uri, const StringAtom& tag);
		void ChangeModel(const StringAtom& uri, const StringAtom& tag);
	};

}

