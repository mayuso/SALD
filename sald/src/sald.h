// Some of this should probably be removed, SALD applications don't need access to all files

// --- Core ----
#include "Sald/Core/Application.h"
#include "Sald/Core/Core.h"
#include "Sald/Core/Input.h"
#include "Sald/Core/KeyCodes.h"
#include "Sald/Core/Layer.h"
#include "Sald/Core/LayerStack.h"
#include "Sald/Core/Log.h"
#include "Sald/Core/MouseCodes.h"
#include "Sald/Core/Window.h"

// --- Events ---
#include "Sald/Events/ApplicationEvent.h"
#include "Sald/Events/Event.h"
#include "Sald/Events/KeyEvent.h"
#include "Sald/Events/MouseEvent.h"

// --- Light ---
#include "Sald/Light/DirectionalLight.h"
#include "Sald/Light/Light.h"
#include "Sald/Light/OmniShadowMap.h"
#include "Sald/Light/PointLight.h"
#include "Sald/Light/ShadowMap.h"
#include "Sald/Light/SpotLight.h"

// --- Renderer ---
#include "Sald/Renderer/Material.h"
#include "Sald/Renderer/RenderCommand.h"
#include "Sald/Renderer/Shader.h"
#include "Sald/Renderer/ShaderManager.h"
#include "Sald/Renderer/Texture.h"
#include "Sald/Renderer/TextureManager.h"

// --- Renderer2D ---
#include "Sald/Renderer/2D/SpriteRenderer.h"

// --- Renderer3D ---
#include "Sald/Renderer/3D/Mesh.h"
#include "Sald/Renderer/3D/Model.h"

// --- Camera ---
#include "Sald/Scene/Camera.h"

// --- Utils ---
#include "Sald/Utils/CommonValues.h"
#include "Sald/Utils/Utils.h"
#include "Sald/Utils/TimeManager.h"
#include "Sald/Utils/Timer.h"

// --- REST --- (Still need to organize these)
#include "Sald/Object.h"
#include "Sald/Skybox.h"
