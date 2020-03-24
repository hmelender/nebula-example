#include "stdneb.h"

#include "game.h"
#include "entity.h"
#include "graphicscomponent.h"
#include "transformcomponent.h"
#include "charactercomponent.h"
#include "motioncomponent.h"

hm::Game* hm::Game::s_Instance = nullptr;
float hm::Game::s_DeltaTime = 0.000001f;
const float& hm::Game::deltaTime = hm::Game::s_DeltaTime;

// Runs on the first frame
void hm::Game::Init()
{
	// m_EntityManager->CreateEntity("ground", "mdl:environment/Groundplane.n3", "Examples");
	// m_EntityManager->CreateEntity("trees", "mdl:Vegetation/Trees_01.n3", "Examples");
	// catapult = &m_EntityManager->CreateEntity("catapult", "mdl:Units/Unit_Catapult.n3", "Examples");
	// placeholder = &m_EntityManager->CreateEntity("placeholder", "mdl:system/placeholder.n3", "Examples");
	// character = &m_EntityManager->CreateCharacter("footman", "mdl:Units/Unit_Footman.n3", "ske:Units/Unit_Footman.nsk3", "ani:Units/Unit_Footman.nax3", "Examples", Math::point(2.0f, 0.0f, -20.0f));
	// light = &m_EntityManager->CreatePointLight("light", Math::float4(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, Math::point(1.0f, 3.5f, 1.0f), 100.0f, true);

	// hm::CharacterComponent& characterComp = character->GetComponent(hm::Component::Type::CHARACTER);
	// characterComp.PlayAnimation(0, 0, Characters::Append, 1.0f, 1, Math::n_rand() * 100.0f, 0.0f, 0.0f, Math::n_rand() * 100.0f);
	// hm::TransformComponent& characterTransform = character->GetComponent(hm::Component::Type::TRANSFORM);
	// hm::MotionComponent& characterMotion = character->CreateComponent(hm::Component::Type::MOTION);
	// 
	// hm::TransformComponent& catapultTransform = catapult->GetComponent("transform");
	// hm::MotionComponent& catapultMotion = catapult->CreateComponent(hm::Component::Type::MOTION);
	// catapultMotion.SetAngularVelocity(Math::float4(0.0f, 1.2f, 0.0f, 0.0f));
	// 
	// hm::TransformComponent& placeholderTransform = placeholder->GetComponent("transform");
	// hm::MotionComponent& placeholderMotion = placeholder->CreateComponent(hm::Component::Type::MOTION);
	// placeholderMotion.SetAngularVelocity(Math::float4(0.0f, -1.0f, 0.0f, 0.0f));
	// 
	// placeholderTransform.SetPosition(Math::point(0.0f, 2.0f, 0.0f));
	// placeholderTransform.SetPivot(Math::point(5.0f, 0.0f, 0.0f));
	// characterMotion.SetVelocity(Math::float4(0.0f, 0.0f, 4.0f, 0.0f));

}

// Runs at the beginning of the frame
void hm::Game::EarlyUpdate(float delta)
{
	Game::s_DeltaTime = delta;

	OnKeyEvent();

}

void hm::Game::Update()
{
	if (m_LoadState) {
		m_EntityManager->LoadSceneState("save_file.dat");
		m_LoadState = false;
	}

	m_EntityManager->Update();

}

// Runs at the end of the frame, after rendering
void hm::Game::LateUpdate()
{

}

void hm::Game::OnKeyEvent()
{
	if (m_KeyInputHandler->KeyPressed(Input::Key::S)) {
		m_EntityManager->SaveSceneState("save_file.dat");
	}
	else if (m_KeyInputHandler->KeyPressed(Input::Key::L)) {
		m_EntityManager->Shutdown();
		m_LoadState = true;
	}
}

void hm::Game::Start(const char* initScript, Input::Keyboard& keyboard)
{
	if (Game::s_Instance != nullptr)
		return;

	Game::s_Instance = this;
	m_EntityManager = &EntityManager::GetInstance();
	m_ScriptServer = Scripting::PythonServer::Create();
	m_ScriptServer->Open();
	Util::String uri("root:");
	uri.Append(initScript);
	Init();
	m_EntityManager->Init();
	m_ScriptServer->EvalFile(uri);
	m_KeyInputHandler = &keyboard;

}

