#pragma once
#include "Core/Components.h"

namespace ProjectCyclone {
  //TODO:

  struct NPCComponent { };

  class NPCSystem {
  public:
    static void OnUpdate(const NPCComponent& component, Oxylus::TransformComponent transform, float deltaTime);
  };
}
