#include "HeliCameraSystem.h"
#include "Utils/Profiler.h"
#include <Scene/Scene.h>
#include <Core/Components.h>
#include "Systems/HeliSystem.h"
#include "Utils/Timestep.h"

namespace ProjectCyclone {
  using namespace Oxylus;

  void HeliCameraSystem::OnUpdate(Scene* scene) {
    ZoneScopedN("Heli Camera System");
    const auto heliView = scene->m_Registry.view<TransformComponent, HeliComponent>();
    const auto cameraView = scene->m_Registry.view<TransformComponent, CameraComponent>();
    for (const auto entity : heliView) {
      auto&& [heliTransform, heli] = heliView.get<TransformComponent, HeliComponent>(entity);
      for (const auto cameraEntity : cameraView) {
        auto&& [cameraTransform, camera] = cameraView.get<TransformComponent, CameraComponent>(cameraEntity);
        m_LastCameraPosition = Math::SmoothDamp(m_LastCameraPosition,
                         heliTransform.Translation,
                         m_TranslationVelocity,
                         TranslationDampening,
                         10000.0f,
                         Timestep::GetDeltaTime());
        cameraTransform.Translation.x = m_LastCameraPosition.x;
        cameraTransform.Translation.z = m_LastCameraPosition.z + 12.0f;
      }
    }
  }
}
