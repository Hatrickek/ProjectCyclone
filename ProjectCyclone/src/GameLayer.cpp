#include "GameLayer.h"

#include <imgui.h>
#include <Assets/AssetManager.h>
#include <Render/Vulkan/VulkanRenderer.h>
#include <Scene/SceneSerializer.h>
#include <Utils/ImGuiScoped.h>

#include "Systems/FreeCamera.h"
#include "Systems/HeliSystem.h"
#include "Systems/NPCSystem.h"

namespace ProjectCyclone {
  GameLayer::~GameLayer() = default;

  void GameLayer::OnAttach() {
    LoadScene();
  }

  void GameLayer::OnDetach() { }

  void GameLayer::OnUpdate(float deltaTime) {
    m_Scene->OnUpdate(deltaTime);

    {
      ZoneScopedN("Heli system");
      const auto group = m_Scene->m_Registry.view<TransformComponent, HeliComponent>();
      for (const auto entity : group) {
        auto&& [transform, heli] = group.get<TransformComponent, HeliComponent>(entity);
        HeliSystem::OnUpdate(heli, deltaTime, transform);
      }
    }
    {
      ZoneScopedN("NPC system");
      const auto group = m_Scene->m_Registry.view<TransformComponent, NPCComponent>();
      for (const auto entity : group) {
        /*auto&& [transform, npc] = group.get<TransformComponent, NPCComponent>(entity);*/
      }
    }
  }

  void GameLayer::OnImGuiRender() {
    RenderFinalImage();
  }

  void GameLayer::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<ReloadSceneEvent>(OX_BIND_EVENT_FN(GameLayer::OnSceneReload));
  }

  void GameLayer::LoadScene() {
    m_Scene = CreateRef<Scene>();
    const SceneSerializer serializer(m_Scene);
    serializer.Deserialize("Assets/Scenes/Main.oxscene");

    m_CameraEntity = m_Scene->FindEntity("Camera");
    m_CameraEntity.AddScript<FreeCamera>();
    m_Scene->FindEntity("Heli").AddComponent<HeliComponent>();
  }

  bool GameLayer::OnSceneReload(ReloadSceneEvent&) {
    OX_CORE_INFO("Scene reloaded.");
    LoadScene();
    return true;
  }

  /*TODO: Proper way to render the final image internally as fullscreen without needing this.
  This a "hack" to render the final image as a fullscreen image.
  Currently the final image in engine renderer is rendered to an offscreen framebuffer image.*/
  void GameLayer::RenderFinalImage() {
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoSavedSettings;
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
