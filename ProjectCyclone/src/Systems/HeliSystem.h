#pragma once
#include "Core/Components.h"
#include "Core/ScriptableEntity.h"

namespace ProjectCyclone {
  struct HeliComponent {
    float Speed = 5.0f;
  };

  class HeliSystem {
  public:
    static void OnUpdate(const HeliComponent& component, float deltaTime, Oxylus::TransformComponent& transform);
  };
}
