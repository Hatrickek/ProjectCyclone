#include "GameLayer.h"

#include <imgui.h>
#include <Assets/AssetManager.h>
#include <Render/Vulkan/VulkanRenderer.h>
#include <Scene/SceneSerializer.h>
#include <Utils/ImGuiScoped.h>

#include "Systems/FreeCamera.h"
#include "Systems/HeliSystem.h"
#include "Systems/NPCSystem.h"
#include "Systems/CrateSystem.h"

#include <entt.hpp>

#include "Systems/HeliCameraSystem.h"

namespace ProjectCyclone {
  GameLayer* GameLayer::s_Instance = nullptr;

  GameLayer::GameLayer() : Layer("Game Layer") {
    s_Instance = this;
  }

  GameLayer::~GameLayer() = default;

  void GameLayer::OnAttach(EventDispatcher& dispatcher) {
    dispatcher.sink<ReloadSceneEvent>().connect<&GameLayer::OnSceneReload>(*this);
    LoadScene();
  }

  void GameLayer::OnDetach() { }

  void GameLayer::OnUpdate(float deltaTime) {
    m_Scene->OnUpdate(deltaTime);
  }

  void GameLayer::OnImGuiRender() {
    RenderFinalImage();

    m_GameUI.Draw(m_Scene);
  }

  void GameLayer::LoadScene() {
    m_Scene = CreateRef<Scene>();
    const SceneSerializer serializer(m_Scene);
    serializer.Deserialize("Assets/Scenes/Main.oxscene");

    m_CameraEntity = m_Scene->FindEntity("Camera");
    m_CameraEntity.AddScript<FreeCamera>();
    m_Scene->FindEntity("Heli").AddComponent<HeliComponent>();

    const auto view = m_Scene->m_Registry.view<NamedComponent>();
    for (const auto entity : view) {
      auto ent = Entity{entity, m_Scene.get()};
      if (ent.GetComponent<NamedComponent>().ComponentName == "CrateComponent") {
        ent.AddComponent<CrateComponent>();
      }
    }

    m_Scene->AddSystem<HeliSystem>()
           ->AddSystem<CrateSystem>()
           ->AddSystem<HeliCameraSystem>();
  }

  bool GameLayer::OnSceneReload(ReloadSceneEvent&) {
    LoadScene();
    OX_CORE_INFO("Scene reloaded.");
    return true;
  }

  /*TODO: Proper way to render the final image internally as fullscreen without needing this.
  This a "hack" to render the final image as a fullscreen image.
  Currently the final image in engine renderer is rendered to an offscreen framebuffer image.*/
  void GameLayer::RenderFinalImage() {
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing
                                    | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGuiScoped::StyleVar style(ImGuiStyleVar_WindowPadding, ImVec2{});
    if (ImGui::Begin("FinalImage", nullptr, flags)) {
      ImGui::Image(VulkanRenderer::GetFinalImage().GetDescriptorSet(),
                   ImVec2{(float)Window::GetWidth(), (float)Window::GetHeight()});
      ImGui::End();
    }
  }
}
