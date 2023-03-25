#include "HeliCameraSystem.h"
#include "Utils/Profiler.h"
namespace ProjectCyclone {
  using namespace Oxylus;
  void HeliCameraSystem::OnUpdate(Scene* scene) {
    ZoneScopedN("Heli Camera System");
    const auto heliView = scene->m_Registry.view<TransformComponent, HeliComponent>();
    const auto camerView = scene->m_Registry.view<>
    for (const auto entity : heliView) {
      auto&& [transform, heli] = crateView.get<TransformComponent, HeliComponent>(entity);
      
    }
}