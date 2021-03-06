cmake_minimum_required(VERSION 3.10)
project(cane)

add_executable(cane
	src/main.h
	src/main.cpp
	src/Editor.h
	src/Editor.cpp
	src/Utility/ez_stream.h
	src/Utility/FileReader.h
	src/Utility/Sigscan.h
	src/Utility/math.h
	src/Utility/math.cpp
	src/Utility/config.h
	src/Utility/config.cpp
	src/Gui/RenderBuffer.h
	src/Gui/RenderBuffer.cpp
	src/Gui/DebugInformation.h
	src/Gui/DebugInformation.cpp
	src/Gui/RendererWindow.h
	src/Gui/RendererWindow.cpp
	src/Gui/ModelBrowser.h
	src/Gui/ModelBrowser.cpp
	src/Gui/ModelViewer.h
	src/Gui/ModelViewer.cpp
	src/Structs/sly_level_structs.h
	src/Structs/sly_level_structs.cpp
	src/Structs/sly_texture_structs.h
	src/Structs/SlyLevelFile.h
	src/Structs/SlyLevelFile.cpp
	src/Renderer/Camera.h
	src/Renderer/Camera.cpp
	src/Renderer/Cube.h
	src/Renderer/Cube.cpp
	src/Renderer/LightingProperties.h
	src/Renderer/Object.h
	src/Renderer/Object.cpp
	src/Renderer/OBJModel.h
	src/Renderer/OBJModel.cpp
	src/Renderer/Shader.h
	src/Renderer/Shader.cpp
)

target_include_directories(cane PUBLIC include)
target_include_directories(cane PRIVATE src)
target_include_directories(cane PRIVATE resources)

set_property(TARGET cane PROPERTY CXX_STANDARD 20)

add_custom_command(TARGET cane POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/resources/colored_object_shader_fragment.glsl		$<TARGET_FILE_DIR:${PROJECT_NAME}>	)
add_custom_command(TARGET cane POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/resources/colored_object_shader_vertex.glsl			$<TARGET_FILE_DIR:${PROJECT_NAME}>	)
add_custom_command(TARGET cane POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/resources/colored_sly_object_shader_fragment.glsl	$<TARGET_FILE_DIR:${PROJECT_NAME}>	)
add_custom_command(TARGET cane POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/resources/colored_sly_object_shader_vertex.glsl		$<TARGET_FILE_DIR:${PROJECT_NAME}>	)
add_custom_command(TARGET cane POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/resources/lit_object_shader_fragment.glsl			$<TARGET_FILE_DIR:${PROJECT_NAME}>	)
add_custom_command(TARGET cane POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/resources/lit_object_shader_vertex.glsl				$<TARGET_FILE_DIR:${PROJECT_NAME}>	)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(cane Threads::Threads)

add_library(glad lib/glad/src/glad.c)
target_include_directories(glad PRIVATE lib/glad/include)
target_include_directories(cane PUBLIC lib/glad/include)
target_link_libraries(cane glad)

add_subdirectory(lib/glfw)
target_link_libraries(cane glfw)

add_subdirectory(include/glm)
target_link_libraries(cane glm)

include_directories(include/imgui)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD=1)
file(GLOB IMGUI_SOURCES include/imgui/*.cpp)
file(GLOB IMGUI_HEADERS include/imgui/*.h)
set(IMGUI_BACKEND_SOURCES
	include/imgui/backends/imgui_impl_opengl3.cpp
	include/imgui/backends/imgui_impl_opengl3.h
	include/imgui/backends/imgui_impl_glfw.h 
	include/imgui/backends/imgui_impl_glfw.cpp)
add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS} ${IMGUI_BACKEND_SOURCES})
target_include_directories(imgui PUBLIC lib/glad/include lib/glfw/include)
target_link_libraries(imgui glad)
target_link_libraries(cane imgui)

add_library(imguifilepicker STATIC include/ImGuiFileDialog/ImGuiFileDialog.cpp)
add_library(dirent STATIC include/dirent/dirent.h include/dirent/dirent.cpp)
set_target_properties(dirent PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(imguifilepicker PUBLIC include/dirent)
target_link_libraries(imguifilepicker dirent)
target_link_libraries(cane imguifilepicker)
