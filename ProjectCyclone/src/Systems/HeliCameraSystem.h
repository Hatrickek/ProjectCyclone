#pragma once
#include <Core/Types.h>

#include "Core/Systems/System.h"

namespace ProjectCyclone {
  class HeliCameraSystem : public Oxylus::System {
  public:
    float TranslationDampening = 0.6f;

    void OnUpdate(Oxylus::Scene* scene) override;
  private:
    Oxylus::Vec3 m_TranslationVelocity = Oxylus::Vec3(0);
    Oxylus::Vec3 m_LastCameraPosition = Oxylus::Vec3(0);
  };
}
