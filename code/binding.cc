#pragma once

#include "pybind11.h"

#include "stdneb.h"
#include "math/float4.h"
#include "math/point.h"
#include "util/stringatom.h"

#include "entitymanager.h"
#include "component.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"
#include "lightcomponent.h"
#include "motioncomponent.h"
#include "charactercomponent.h"


using Util::StringAtom;
using Math::float4;
using Math::point;

using hm::EntityManager;
using hm::Entity;
using hm::Component;
using hm::TransformComponent;
using hm::GraphicsComponent;
using hm::LightComponent;
using hm::MotionComponent;
using hm::CharacterComponent;

PYBIND11_MODULE(hmbind, m) {
	m.doc() = "nebula engine bind";

	py::class_<float4>(m, "float4")
		.def(py::init<float, float, float, float>());
	py::class_<point>(m, "point")
		.def(py::init<float, float, float>());
	py::class_<StringAtom>(m, "StringAtom")
		.def(py::init<const char*>());

	py::class_<hm::EntityManager>(m, "EntityManager")
		.def_static("__new__", [](py::object) { return EntityManager::GetInstance(); }, py::return_value_policy::reference_internal)

		.def("createEntity", py::overload_cast<
			const StringAtom&, const StringAtom&, const StringAtom&>(&EntityManager::CreateEntity),
			py::return_value_policy::reference, "Create entity", py::arg("name"), py::arg("uri"), py::arg("tag"))

		.def("createEntity", py::overload_cast<
			const StringAtom&, const StringAtom&, const StringAtom&, const point&>(&EntityManager::CreateEntity),
			py::return_value_policy::reference, "Create entity at position", py::arg("name"), py::arg("uri"), py::arg("tag"), py::arg("position"))

		.def("createPointLight", &EntityManager::CreatePointLight, py::return_value_policy::reference, "Create point light",
			py::arg("name"), py::arg("color"), py::arg("intensity"), py::arg("position"), py::arg("range"), py::arg("castShadows"))

		.def("createCharacter", py::overload_cast<
			const StringAtom&, const StringAtom&, const StringAtom&, const StringAtom&, const StringAtom&, const point&>(&EntityManager::CreateCharacter),
			py::return_value_policy::reference, "Create character at position",
			py::arg("name"), py::arg("modelUri"), py::arg("skeletonUri"), py::arg("animationUri"), py::arg("tag"), py::arg("position"))

		.def("getEntity", &EntityManager::GetEntity, py::return_value_policy::reference, "Get entity by name",
			py::arg("name"));

	py::class_<Component> cmp(m, "Component");
	py::enum_<Component::Type>(cmp, "Type")
		.value("TRANSFORM", Component::Type::TRANSFORM)
		.value("GRAPHICS", Component::Type::GRAPHICS)
		.value("LIGHT", Component::Type::LIGHT)
		.value("CHARACTER", Component::Type::CHARACTER)
		.value("MOTION", Component::Type::MOTION);

	py::class_<Entity> ent(m, "Entity");
		ent.def("getTransformComponent", [](Entity& e) { 
			return dynamic_cast<TransformComponent&>(e.GetComponent(Component::Type::TRANSFORM));
			}, py::return_value_policy::reference);
		ent.def("getGraphicsComponent", [](Entity& e) {
			return dynamic_cast<GraphicsComponent&>(e.GetComponent(Component::Type::GRAPHICS));
			}, py::return_value_policy::reference);
		ent.def("getLightComponent", [](Entity& e) {
			return dynamic_cast<LightComponent&>(e.GetComponent(Component::Type::LIGHT));
			}, py::return_value_policy::reference);
		ent.def("getCharacterComponent", [](Entity& e) {
			return dynamic_cast<CharacterComponent&>(e.GetComponent(Component::Type::CHARACTER));
			}, py::return_value_policy::reference);
		ent.def("getMotionComponent", [](Entity& e) {
			return dynamic_cast<MotionComponent&>(e.GetComponent(Component::Type::MOTION));
			}, py::return_value_policy::reference);

		ent.def("createMotionComponent", [](Entity& e) {
			return dynamic_cast<MotionComponent&>(e.CreateComponent(Component::Type::MOTION));
			}, py::return_value_policy::reference);


	py::class_<TransformComponent, Component> trf(m, "TransformComponent");
		trf.def("setPosition", py::overload_cast<const point&>(&TransformComponent::SetPosition), py::arg("position"));
		trf.def("setPosition", py::overload_cast<float, float, float>(&TransformComponent::SetPosition), py::arg("x"), py::arg("y"), py::arg("z"));
		trf.def("translate", py::overload_cast<const float4&>(&TransformComponent::Translate), py::arg("vector"));
		trf.def("translate", py::overload_cast<float, float, float>(&TransformComponent::Translate), py::arg("x"), py::arg("y"), py::arg("z"));
		trf.def("setRotation", &TransformComponent::SetRotationEuler, py::arg("x"), py::arg("y"), py::arg("z"));
		trf.def("rotateVector", py::overload_cast<const float4&, float>(&TransformComponent::RotateAxis), py::arg("vector"), py::arg("angle"));
		trf.def("rotateAxis", py::overload_cast<TransformComponent::Axis, float>(&TransformComponent::RotateAxis), py::arg("axis"), py::arg("angle"));
		trf.def("setScale", py::overload_cast<float>(&TransformComponent::SetScale), py::arg("scale"));
		trf.def("setScale", py::overload_cast<const float4&>(&TransformComponent::SetScale), py::arg("vector"));
		trf.def("setScale", py::overload_cast<float, float, float>(&TransformComponent::SetScale), py::arg("x"), py::arg("y"), py::arg("z"));
		trf.def("setPivot", &TransformComponent::SetPivot, py::arg("position"));

		py::enum_<TransformComponent::Axis>(trf, "Axis")
			.value("X", TransformComponent::Axis::X)
			.value("Y", TransformComponent::Axis::Y)
			.value("Z", TransformComponent::Axis::Z);

	py::class_<GraphicsComponent, Component>(m, "GraphicsComponent")
		.def("changeModel", &GraphicsComponent::ChangeModel, py::arg("uri"), py::arg("tag"));

	py::class_<CharacterComponent, Component> chr(m, "CharacterComponent");
		chr.def("playAnimation", &CharacterComponent::PlayAnimation, 
			py::arg("clipIndex"), py::arg("track"), py::arg("mode"), py::arg("weight") = 1.0f, py::arg("loopCount") = 1, py::arg("startTime") = 0.0f,
			py::arg("fadeIn") = 0.0f, py::arg("fadeOut") = 0.0f, py::arg("timeOffset") = 0.0f, py::arg("timeFactor") = 1.0f);

	py::enum_<Characters::EnqueueMode>(chr, "EnqueueMode")
		.value("APPEND", Characters::EnqueueMode::Append)
		.value("IGNORE_IF_SAME", Characters::EnqueueMode::IgnoreIfSame)
		.value("REPLACE", Characters::EnqueueMode::Replace);

	py::class_<MotionComponent, Component> mot(m, "MotionComponent");
		mot.def("setVelocity", &MotionComponent::SetVelocity, py::arg("vector"));
		mot.def("setAngularVelocity", &MotionComponent::SetAngularVelocity, py::arg("vector"));
		mot.def("modifyVelocity", &MotionComponent::ModifyVelocity, py::arg("vector"));
		mot.def("modifyAngularVelocity", &MotionComponent::ModifyAngularVelocity, py::arg("vector"));

}