cmake_minimum_required(VERSION 3.5)
project(engine_saidou VERSION 1.0.0)

# Politique CMake pour OpenGL
cmake_policy(SET CMP0072 NEW)

#Option pour sélectionner la plateforme
option(TARGET_PLATFORM "Choose the target platform (windows, linux, android, ios)" "windows")

# Ajoutez les fichiers d'en-tête et source manuellement
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(INCLUDE_DIR_ENGINE "${CMAKE_SOURCE_DIR}/include/Engine")
set(INCLUDE_DIR_GAME "${CMAKE_SOURCE_DIR}/include/Game")
set(INCLUDE_DIR_MATH "${CMAKE_SOURCE_DIR}/include/Math")
set(INCLUDE_DIR_UTILITIES "${CMAKE_SOURCE_DIR}/include/Utilities")
set(INCLUDE_DIR_IMGUI "${CMAKE_SOURCE_DIR}/include/ImGUI")

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

# Déterminer la plateforme cible
if(TARGET_PLATFORM STREQUAL "windows")
    message(STATUS "Configuring for Windows...")
    set(GLFW_LIB_PATH "${LIB_DIR}/Windows")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
elseif(TARGET_PLATFORM STREQUAL "linux")
    message(STATUS "Configuring for Linux...")
    set(GLFW_LIB_PATH "${LIB_DIR}/Linux")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
elseif(TARGET_PLATFORM STREQUAL "android")
    message(STATUS "Configuring for Android...")
    set(GLFW_LIB_PATH "${LIB_DIR}/Android")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
elseif(TARGET_PLATFORM STREQUAL "ios")
    message(STATUS "Configuring for IOS...")
    set(GLFW_LIB_PATH "${LIB_DIR}/IOS")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
else()
    message(STATUS "Unsupported or Not Found Platform: ${TARGET_PLATFORM}")
endif()

# Inclure les répertoires pour les en-têtes
include_directories(${INCLUDE_DIR})

# Ajouter les fichiers source
add_executable(engine_saidou
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/glad.c

    ${SRC_DIR}/Engine/Engine.cpp
    ${SRC_DIR}/Engine/Window.cpp
    ${SRC_DIR}/Engine/Shader.cpp
    ${SRC_DIR}/Engine/Mesh.cpp
    ${SRC_DIR}/Engine/MeshRenderer.cpp
    ${SRC_DIR}/Engine/Camera.cpp
    ${SRC_DIR}/Engine/Transform.cpp
    ${SRC_DIR}/Engine/Color.cpp
    ${SRC_DIR}/Engine/Material.cpp
    ${SRC_DIR}/Engine/Light.cpp
    ${SRC_DIR}/Engine/LightingSettings.cpp
    ${SRC_DIR}/Engine/SpotLight.cpp
    ${SRC_DIR}/Engine/DirectionalLight.cpp
    ${SRC_DIR}/Engine/PointLight.cpp
    ${SRC_DIR}/Engine/Assets.cpp
    ${SRC_DIR}/Engine/AssetsManager.cpp
    ${SRC_DIR}/Engine/Component.cpp
    ${SRC_DIR}/Engine/Entity.cpp
    ${SRC_DIR}/Engine/World.cpp

    ${SRC_DIR}/Game/DirectionalLightController.cpp
    ${SRC_DIR}/Game/DirectionalLightEntity.cpp

    ${SRC_DIR}/Utilities/TransformationUtilities.cpp
    ${SRC_DIR}/Utilities/MeshUtilities.cpp
    ${SRC_DIR}/Utilities/Logger.cpp
    ${SRC_DIR}/Utilities/FileSystem.cpp
    ${SRC_DIR}/Utilities/stb_image.cpp
    ${SRC_DIR}/Utilities/Texture.cpp
    ${SRC_DIR}/Utilities/TimeEngine.cpp
    ${SRC_DIR}/Utilities/ImGUI_Test.cpp

    ${SRC_DIR}/ImGUI/imgui.cpp
    ${SRC_DIR}/ImGUI/imgui_draw.cpp
    ${SRC_DIR}/ImGUI/imgui_tables.cpp
    ${SRC_DIR}/ImGUI/imgui_widgets.cpp
    ${SRC_DIR}/ImGUI/backends/imgui_impl_glfw.cpp
    ${SRC_DIR}/ImGUI/backends/imgui_impl_opengl3.cpp

    ${SRC_DIR}/Math/Mathf.cpp
    ${SRC_DIR}/Math/Vector2.cpp
    ${SRC_DIR}/Math/Vector3.cpp
    ${SRC_DIR}/Math/Vector4.cpp
    ${SRC_DIR}/Math/Matrix2x2.cpp
    ${SRC_DIR}/Math/Matrix3x3.cpp
    ${SRC_DIR}/Math/Matrix4x4.cpp
    ${SRC_DIR}/Math/Quaternion.cpp
)

# Configuration du sous-système pour Debug et Release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(engine_saidou PROPERTIES
        WIN32_EXECUTABLE TRUE  # Pas de console en Release
    )
else()
    set_target_properties(engine_saidou PROPERTIES
        WIN32_EXECUTABLE FALSE # Console activée en Debug
    )
endif()

# Lier OpenGL (déjà fourni par le système ou le SDK)
find_package(OpenGL REQUIRED)
target_link_libraries(engine_saidou OpenGL::GL)

# Ajouter le lien pour GLFW (directement à partir de votre répertoire include)
target_link_directories(engine_saidou PRIVATE ${GLFW_LIB_PATH})
target_include_directories(engine_saidou PRIVATE ${INCLUDE_DIR})
target_include_directories(engine_saidou PRIVATE ${INCLUDE_DIR_ENGINE})
target_include_directories(engine_saidou PRIVATE ${INCLUDE_DIR_GAME})
target_include_directories(engine_saidou PRIVATE ${INCLUDE_DIR_MATH})
target_include_directories(engine_saidou PRIVATE ${INCLUDE_DIR_UTILITIES})
target_include_directories(engine_saidou PRIVATE ${INCLUDE_DIR_IMGUI})
target_include_directories(engine_saidou PRIVATE ${INCLUDE_DIR_IMGUI}/backends)
target_link_libraries(engine_saidou glfw3)

# Copier les dossiers `assets` vers le répertoire de sortie
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/shaders)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures)

add_custom_command(
    TARGET engine_saidou POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

# Configurer les builds Debug et Release
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)