include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)


# .................................
# GLFW
# .................................

message(STATUS "Finding package Glfw3...")
find_package(glfw3 CONFIG REQUIRED)
message(STATUS "Done")

# .................................
# IMGUI
# .................................

message(STATUS "Installing ImGui...")
FetchContent_Declare(
    imgui_sources
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.90.5-docking)
FetchContent_Populate(imgui_sources)

file(GLOB IMGUI_SOURCES 
	${imgui_sources_SOURCE_DIR}/*.cpp
	${imgui_sources_SOURCE_DIR}/*.h
    ${imgui_sources_SOURCE_DIR}/backends/imgui_impl_glfw*
	${imgui_sources_SOURCE_DIR}/backends/imgui_impl_opengl3.h
    ${imgui_sources_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${imgui_sources_SOURCE_DIR})
target_link_libraries(imgui PUBLIC glfw)
message(STATUS "Done")


# .................................
# Glad
# .................................

set(glad_SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/GLAD)
add_library(glad 
    ${glad_SOURCE_DIR}/src/glad.c
    ${glad_SOURCE_DIR}/include/glad/glad.h
    ${glad_SOURCE_DIR}/include/KHR/khrplatform.h)
target_include_directories(glad PUBLIC ${glad_SOURCE_DIR}/include)


# # .................................
# # GLM
# # .................................

# message(STATUS "Installing Glm...")
# FetchContent_Declare(
#     glm_sources
#     GIT_REPOSITORY https://github.com/g-truc/glm.git
#     GIT_TAG 1.0.1)
# FetchContent_MakeAvailable(glm_sources)
# message(STATUS "Done")

# .................................
# LibTIFF
# .................................

message(STATUS "Finding package LibTIFF...")
find_package(TIFF CONFIG REQUIRED)
# - SOME_LIBRARY_DLL: /path/to/dependencies/bin/some.dll
# - SOME_LIBRARY: /path/to/dependencies/lib/some.lib
# - SOME_INCLUDE_DIRS: /path/to/dependencies/include
set(TIFF_DLL "C:/Program Files (x86)/tiff/bin/tiffd.dll")
set(TIFF_LIB "C:/Program Files (x86)/tiff/lib/tiffd.lib")
set(TIFF_INC "C:/Program Files (x86)/tiff/include")
set_target_properties(TIFF::tiff PROPERTIES
    IMPORTED_LOCATION "${TIFF_DLL}"
    IMPORTED_IMPLIB "${TIFF_LIB}"
    INTERFACE_INCLUDE_DIRECTORIES "${TIFF_INC}"
)
message(STATUS "Done")


