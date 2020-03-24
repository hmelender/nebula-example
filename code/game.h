#pragma once

#include "scripting/python/pythonserver.h"
#include "input/keyboard.h"

#include "entitymanager.h"
#include <stdexcept>

namespace hm
{
	class Entity;

	class Game
	{
	private:
		EntityManager* m_EntityManager;
		Scripting::PythonServer* m_ScriptServer;
		Input::Keyboard* m_KeyInputHandler;
		static float s_DeltaTime;
		static Game* s_Instance;
		bool m_LoadState = false;

		//--------------------------------------------------------------------
		hm::Entity* character;
		hm::Entity* catapult;
		hm::Entity* placeholder;
		hm::Entity* light;
		//--------------------------------------------------------------------
		void Init();
		void OnKeyEvent();
	public:
		Game() : m_EntityManager(nullptr), m_ScriptServer(nullptr)
		{
			if (Game::s_Instance != nullptr) {
				throw std::runtime_error("Game instance already exists!");
			}
		};

		~Game() {
			if (m_EntityManager != nullptr) {
				m_EntityManager->Shutdown();
				delete m_EntityManager;
			}
		};

		static const float& deltaTime;

		static Game* GetInstance() {
			return Game::s_Instance;
		};

		void Start(const char* initScript, Input::Keyboard& keyboard);
		void EarlyUpdate(float delta);
		void Update();
		void LateUpdate();
	};

};
