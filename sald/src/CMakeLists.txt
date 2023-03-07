
target_precompile_headers(${PROJECT_NAME} PRIVATE saldpch.h)

target_sources(sald
    PRIVATE

    PUBLIC
    Sald/Core/Application.cpp
    Sald/Core/Input.cpp
    Sald/Core/Layer.cpp
    Sald/Core/LayerStack.cpp
    Sald/Core/Log.cpp
    Sald/Core/Window.cpp

    Sald/Light/DirectionalLight.cpp
    Sald/Light/Light.cpp
    Sald/Light/OmniShadowMap.cpp
    Sald/Light/PointLight.cpp
    Sald/Light/ShadowMap.cpp
    Sald/Light/SpotLight.cpp

    Sald/Renderer/Material.cpp

    Sald/Renderer/OpenGLContext.cpp
    Sald/Renderer/Renderer.cpp
    Sald/Renderer/Shader.cpp
    Sald/Renderer/ShaderManager.cpp
    Sald/Renderer/Texture.cpp
    Sald/Renderer/TextureManager.cpp

    Sald/Renderer/2D/Renderer2D.cpp
    Sald/Renderer/2D/SpriteRenderer.cpp

    Sald/Renderer/3D/Mesh.cpp
    Sald/Renderer/3D/Model.cpp
    Sald/Renderer/3D/Renderer3D.cpp

    Sald/Scene/Camera.cpp

    Sald/Utils/Utils.cpp
    Sald/Utils/TimeManager.cpp
    Sald/Utils/Timer.cpp

    Sald/Object.cpp
    Sald/Skybox.cpp
)

target_include_directories(sald
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/../vendor/glfw/include
    ${CMAKE_CURRENT_LIST_DIR}/../vendor/glad/include
    ${CMAKE_CURRENT_LIST_DIR}/../vendor/glm
    ${CMAKE_CURRENT_LIST_DIR}/../vendor/stb
    ${CMAKE_CURRENT_LIST_DIR}/../vendor/assimp/include
    ${CMAKE_CURRENT_LIST_DIR}/../vendor/spdlog/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm assimp spdlog)