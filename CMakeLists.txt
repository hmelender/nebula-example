# Nebula Example

# 3.7.2 required for using FindVulkan
cmake_minimum_required(VERSION 3.7.2)

get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include(${FIPS_ROOT_DIR}/cmake/fips.cmake)
include(${FIPS_ROOT_DIR}/cmake/fips.cmake)

fips_setup(PROJECT nebula-env-project)
fips_include_directories(.)

# fips_add_subdirectory(pybind11)
# pybind11_add_module(nebula-env-binding code/binding.cc)


nebula_begin_app(nebula-env windowed)
    
    fips_dir(code)
        fips_files(
            main.cc
            exampleapp.cc
            exampleapp.h
			entitymanager.cc
			entitymanager.h
			entity.cc
			entity.h
			component.cc
			component.h
			graphicscomponent.cc
			graphicscomponent.h
			transformcomponent.cc
			transformcomponent.h
			lightcomponent.cc
			lightcomponent.h
			charactercomponent.cc
			charactercomponent.h
			motioncomponent.cc
			motioncomponent.h
			message.cc
			message.h
			variant_ext.h
			serializer.h
			serializer.cc
			binding.h
			binding.cc
        )

    fips_deps(foundation render resource dynui scripting)
nebula_end_app()

fips_finish()
