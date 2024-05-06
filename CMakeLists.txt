cmake_minimum_required(VERSION 3.26)
project(HLAEngine)

# find_package(glfw3 CONFIG REQUIRED)
# find_package(OpenGL CONFIG REQUIRED)
# find_package(glad REQUIRED)
# find_package(TIFF CONFIG REQUIRED)

set(RESOURCES_PATH ${CMAKE_SOURCE_DIR}/resources)
add_compile_definitions(RESOURCES_PATH=\"${RESOURCES_PATH}\")
add_compile_definitions(TEXTURES_PATH=\"${RESOURCES_PATH}/textures\")

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compilation and optimization flags
if(MSVC)
        SET(CMAKE_CXX_FLAGS_DEBUG "/MP /EHsc /Od /ZI")
        SET(CMAKE_CXX_FLAGS_RELEASE "/MP /EHsc /O2")

        # Set debug dir
        # set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_ROOT}/resources")
else()
        SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -Wextra")
        SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra")
endif()


# Download, install and search third party libraries
include(cmake/third_party.cmake)


if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
    # file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.h)
	file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
	file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/inc/*.hpp ${CMAKE_SOURCE_DIR}/inc/*.h)
	file(GLOB_RECURSE LIBRARY_HEADERS ${CMAKE_SOURCE_DIR}/libraries/inc/*.hpp ${CMAKE_SOURCE_DIR}/libraries/inc/*.h)
else()
	file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
	file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/inc/*.hpp ${CMAKE_SOURCE_DIR}/inc/*.h)
	file(GLOB LIBRARY_HEADERS ${CMAKE_SOURCE_DIR}/libraries/inc/*.hpp ${CMAKE_SOURCE_DIR}/libraries/inc/*.h)

endif()


# For better display in IDEs
SOURCE_GROUP(TREE ${CMAKE_SOURCE_DIR}/src PREFIX Sources FILES ${SOURCES})
SOURCE_GROUP(TREE ${CMAKE_SOURCE_DIR}/inc PREFIX Headers FILES ${HEADERS})
SOURCE_GROUP(TREE ${CMAKE_SOURCE_DIR}/libraries/inc PREFIX Library_Headers FILES ${LIBRARY_HEADERS})


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/libraries/inc)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw TIFF::tiff imgui)

# if(MSVC)
# 	# Set startup project
# 	set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
# endif()

# Create a dummy target to make resources visibles in IDEs
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
	file(GLOB_RECURSE SHADERS ${CMAKE_SOURCE_DIR}/resources/shaders/*)
	file(GLOB_RECURSE DATA ${CMAKE_SOURCE_DIR}/resources/data/*)
	file(GLOB_RECURSE TEXTURES ${CMAKE_SOURCE_DIR}/resources/textures/*)
else()
	file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/resources/shaders/*)
	file(GLOB DATA ${CMAKE_SOURCE_DIR}/resources/data/*)
	file(GLOB TEXTURES ${CMAKE_SOURCE_DIR}/resources/textures/*)
endif()

SOURCE_GROUP(TREE ${CMAKE_SOURCE_DIR}/resources/shaders PREFIX shaders FILES ${SHADERS})
SOURCE_GROUP(TREE ${CMAKE_SOURCE_DIR}/resources/textures PREFIX textures FILES ${TEXTURES})
SOURCE_GROUP(TREE ${CMAKE_SOURCE_DIR}/resources/data PREFIX data FILES ${DATA})
add_custom_target(resources SOURCES ${SHADERS} ${DATA} ${TEXTURES})