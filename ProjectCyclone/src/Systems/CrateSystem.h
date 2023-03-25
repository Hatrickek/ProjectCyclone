#pragma once
#include "Core/Systems/System.h"

namespace ProjectCyclone {
  struct CrateComponent {
    int Score = 1;
  };

  class CrateSystem : public Oxylus::System {
  public:
    CrateSystem() = default;
    void OnUpdate(Oxylus::Scene* scene) override;
  };
}
