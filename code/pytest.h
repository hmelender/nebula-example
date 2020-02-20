#include "pybind11.h"
#include "entitymanager.h"

int add(int i, int j) {
	return i + j;
}

hm::EntityManager& entityManager = hm::EntityManager::GetInstance();

PYBIND11_MODULE(hmbind, m) {
	m.doc() = "nebula engine bind";

	py::class_<hm::Entity>(m, "Entity")
		.def("getTransform", &hm::Entity::GetComponent, py::arg("name"));

	py::class_<hm::EntityManager>(m, "EntityManager")
		.def_static("createEntity", &entityManager.GetEntity, py::return_value_policy::reference, "Get entity by name",
			py::arg("name"));

}