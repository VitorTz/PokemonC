cmake_minimum_required(VERSION 3.22...3.30)
project(PokemonC)


include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

# Our Project
add_executable(${PROJECT_NAME} "src/main.cpp" "src/ecs/component/components.h" "src/constants.h" "src/ecs/component/ComponentManager.h" "src/ecs/system/SystemManager.h" "src/ecs/system/SystemManager.cpp" "src/ecs/entity/EntityManager.h" "src/ecs/entity/EntityManager.cpp" "src/ecs/system/SystemSprite.cpp" "src/ecs/system/SystemSpriteAnimation.cpp" "src/ecs/ECS.h" "src/ecs/ECS.cpp" "src/ecs/component/ComponentManager.cpp" "src/util/Camera.h" "src/util/Camera.cpp" "src/scene/Scene.h" "src/scene/Scene.cpp" "src/scene/TitleScreen.cpp" "src/scene/World.cpp" "src/scene/FireArena.cpp" "src/scene/PlantArena.cpp" "src/scene/WaterArena.cpp" "src/scene/Hospital.cpp" "src/scene/House.cpp" "src/scene/TestScene.cpp" "src/ui/image.h" "src/util/TexturePool.h" "src/util/TexturePool.cpp" "src/util/util.h" "src/util/util.cpp" "src/ecs/component/components.cpp" "src/ecs/system/SystemPlayer.cpp" "src/pokemon.h" "src/ecs/system/SystemCharacter.cpp" "src/util/Collision.h" "src/util/Collision.cpp" "src/util/debug.h" "src/util/debug.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if ("${PLATFORM}" STREQUAL "Web")
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/../resources
    )
    #DEPENDS ${PROJECT_NAME}
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    )
    #DEPENDS ${PROJECT_NAME}
endif()

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file resources)
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
