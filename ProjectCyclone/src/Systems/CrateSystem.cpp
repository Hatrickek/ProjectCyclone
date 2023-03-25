#include "CrateSystem.h"

#include "HeliSystem.h"
#include "Core/Entity.h"
#include "Scene/Scene.h"

namespace ProjectCyclone {
  using namespace Oxylus;

  void CrateSystem::OnUpdate(Scene* scene) {
    ZoneScopedN("Crate system");
    const auto heliView = scene->m_Registry.view<TransformComponent, HeliComponent>();
    const auto crateView = scene->m_Registry.view<TransformComponent, CrateComponent>();
    for (const auto entity : crateView) {
      auto&& [transform, crate] = crateView.get<TransformComponent, CrateComponent>(entity);
      const auto ent = Entity{entity, scene};
      constexpr float axisThreshold = 0.5f;

      for (const auto heliEntity : heliView) {
        auto&& [heliTransform, heli] = heliView.get<TransformComponent, HeliComponent>(heliEntity);
        if (std::abs(transform.Translation.x - heliTransform.Translation.x) < axisThreshold
            && std::abs(transform.Translation.y + 0.2f - heliTransform.Translation.y) < axisThreshold
            && std::abs(transform.Translation.z - heliTransform.Translation.z) < axisThreshold) {
          heli.CratesTaken += 1;
          scene->DestroyEntity(ent);
          break;
        }
      }
    }
  }
}
