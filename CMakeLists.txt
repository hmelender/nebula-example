# Nebula Example

# 3.7.2 required for using FindVulkan
cmake_minimum_required(VERSION 3.7.2)

get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include(${FIPS_ROOT_DIR}/cmake/fips.cmake)

fips_setup(PROJECT nebula-env-project)
fips_include_directories(.)

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
			variant_ext.h
			pybind11.h
			message.h
			message.cc
        )

    fips_deps(foundation render resource dynui scripting)
nebula_end_app()

fips_finish()
