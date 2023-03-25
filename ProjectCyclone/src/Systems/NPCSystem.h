#pragma once
#include "Core/Systems/System.h"

namespace ProjectCyclone {
  struct NPCComponent { };

  class NPCSystem : Oxylus::System {
  public:
    void OnUpdate(Oxylus::Scene* scene);
  };
}
