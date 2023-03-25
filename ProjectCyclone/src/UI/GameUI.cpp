#include "GameUI.h"

#include <imgui.h>

#include "UI/OxUI.h"
#include <icons/IconsMaterialDesignIcons.h>
#include "Utils/StringUtils.h"
#include "GameLayer.h"

namespace ProjectCyclone {
  using namespace Oxylus;

  void GameUI::Draw(Ref<Scene>& scene) const {
    constexpr auto windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking |
                                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
                                 ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    const HeliComponent* heliComponent = nullptr;
    auto& registery = scene->m_Registry;
    const auto group = registery.view<TransformComponent, HeliComponent>();
    for (const auto entity : group) {
      auto&& [transform, heli] = group.get<TransformComponent, HeliComponent>(entity);
      heliComponent = &heli;
    }
    const auto Time = GameLayer::Get()->Time;
    constexpr float PAD = 10.0f;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
    ImVec2 window_pos;
    window_pos.x = (work_pos.x + PAD);
    window_pos.y = work_pos.y + PAD;
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::SetNextWindowSize({200, 0}, ImGuiCond_Always);
    auto heliWindowSize = ImGui::GetWindowSize();
    if (ImGui::Begin("HeliUI", nullptr, windowFlags)) {
      heliWindowSize = ImGui::GetWindowSize();
      OxUI::BeginUI();
      OxUI::ProgressBar("Time        ", Time);
      OxUI::ProgressBar("Fuel", heliComponent->Fuel);
      OxUI::Property("Altitude", "%.1f", heliComponent->Altitude);
      OxUI::EndUI();
      ImGui::End();
    }

    constexpr auto MAX_NUMBER_OF_CRATES = 5;

    window_pos = ImVec2{work_pos.x + PAD, work_pos.y + heliWindowSize.y + PAD * 2};
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::SetNextWindowSize({200, 0}, ImGuiCond_Always);
    if (ImGui::Begin("CrateUI", nullptr, windowFlags)) {
      for (int32_t i = 0; i < MAX_NUMBER_OF_CRATES - heliComponent->CratesTaken; i++) {
        ImGui::Text(StringUtils::FromChar8T(ICON_MDI_CUBE));
        ImGui::SameLine();
      }
      ImGui::End();
    }
  }
}
