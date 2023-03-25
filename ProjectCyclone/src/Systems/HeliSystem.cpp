#include "HeliSystem.h"
#include "Core/Entity.h"
#include "Core/Input.h"
#include "Utils/Timestep.h"

using namespace Oxylus;

namespace ProjectCyclone {
  void HeliSystem::OnUpdate(Scene* scene) {
    ZoneScopedN("Heli System");

    auto& registery = scene->m_Registry;
    const auto group = registery.view<TransformComponent, HeliComponent>();
    for (const auto entity : group) {
      auto&& [transform, heli] = group.get<TransformComponent, HeliComponent>(entity);
      if (Input::GetKeyDown(Key::W)) {
        transform.Translation.z += heli.Speed * Timestep::GetDeltaTime();
      }
      else if (Input::GetKeyDown(Key::S)) {
        transform.Translation.z -= heli.Speed * Timestep::GetDeltaTime();
      }
      else if (Input::GetKeyDown(Key::A)) {
        transform.Translation.x -= heli.Speed * Timestep::GetDeltaTime();
      }
      else if (Input::GetKeyDown(Key::D)) {
        transform.Translation.x += heli.Speed * Timestep::GetDeltaTime();
      }

      //Move vertical
      if (Input::GetKeyDown(Key::Q) && heli.Altitude >= 0.2f) {
        transform.Translation.y -= heli.Speed * Timestep::GetDeltaTime();
      }
      else if (Input::GetKeyDown(Key::E) && heli.Altitude < 8.0f) {
        transform.Translation.y += heli.Speed * Timestep::GetDeltaTime();
      }

      heli.Fuel -= 0.1f * ImGui::GetIO().DeltaTime;
      heli.Altitude = transform.Translation.y;

      auto ent = Entity{entity, scene};
      ent.GetChild(1).GetComponent<TransformComponent>().Rotation.y += 5.0f;
    }
  }
}
