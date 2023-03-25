#pragma once
#include "Core/Systems/System.h"

namespace ProjectCyclone {
  class HeliCameraSystem : public Oxylus::System {
  public:
    void OnUpdate(Oxylus::Scene* scene) override;
  };
}
