#include "HeliSystem.h"

#include "Core/Input.h"

using namespace Oxylus;

namespace ProjectCyclone {
  void HeliSystem::OnUpdate(const HeliComponent& component, const float deltaTime, TransformComponent& transform) {
    //Move horizontal
    if (Input::GetKeyDown(Key::W)) {
      transform.Translation.z += component.Speed * deltaTime;
    }
    else if (Input::GetKeyDown(Key::S)) {
      transform.Translation.z -= component.Speed * deltaTime;
    }
    else if (Input::GetKeyDown(Key::A)) {
      transform.Translation.x -= component.Speed * deltaTime;
    }
    else if (Input::GetKeyDown(Key::D)) {
      transform.Translation.x += component.Speed * deltaTime;
    }

    //Move vertical
    if (Input::GetKeyDown(Key::Q)) {
      transform.Translation.y -= component.Speed * deltaTime;
    }
    else if (Input::GetKeyDown(Key::E)) {
      transform.Translation.y += component.Speed * deltaTime;
    }
  }
}
