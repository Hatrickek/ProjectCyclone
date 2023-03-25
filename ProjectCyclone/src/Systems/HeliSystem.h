#pragma once
#include "Core/Systems/System.h"

namespace ProjectCyclone {
  struct HeliComponent {
    float Speed = 5.0f;
    float Fuel = 1.0f; //1.0f = Full, 0.0f = Empty
    float Altitude = 5.0f;
    int32_t CratesTaken = 0;
  };

  class HeliSystem : public Oxylus::System {
  public:
    HeliSystem() = default;
    ~HeliSystem() override = default;
    void OnUpdate(Oxylus::Scene* scene) override;
  };
}
