#pragma once
#include "Core/Base.h"
#include "Systems/HeliSystem.h"

namespace ProjectCyclone {
  class GameUI {
  public :
    GameUI() = default;
    ~GameUI() = default;

    void Draw(Oxylus::Ref<Oxylus::Scene>& scene) const;

  };
}
