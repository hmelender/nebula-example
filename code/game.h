#pragma once

#include "scripting/python/pythonserver.h"

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
		static float s_DeltaTime;
		static Game* s_Instance;
		//--------------------------------------------------------------------
		hm::Entity* character;
		hm::Entity* catapult;
		hm::Entity* placeholder;
		hm::Entity* light;
		float timer = 0.0f;
		bool saveScene = false;
		bool loadScene = false;
		//--------------------------------------------------------------------
		void Init();
	public:
		Game() : m_EntityManager(nullptr), m_ScriptServer(nullptr)
		{
			if (Game::s_Instance != nullptr) {
				throw std::runtime_error("Game instance already exists!");
			}
		};

		~Game() {
			if (Game::s_Instance != nullptr)
				if (Game::s_Instance->m_EntityManager != nullptr) {
					Game::s_Instance->m_EntityManager->Shutdown();
					delete Game::s_Instance->m_EntityManager;
				}
				delete Game::s_Instance;
		};

		static const float& deltaTime;

		static Game* GetInstance() {
			return Game::s_Instance;
		};

		void Start(const char* initScript);
		void EarlyUpdate(float delta);
		void Update();
		void LateUpdate();
	};

};
