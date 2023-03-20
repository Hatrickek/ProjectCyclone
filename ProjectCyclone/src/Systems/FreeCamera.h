#pragma once
#include "Core/ScriptableEntity.h"
#include "Render/Camera.h"

namespace ProjectCyclone {
  class FreeCamera : public Oxylus::ScriptableEntity {
  protected:
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
    void OnDestroy() override;

  private:
    Oxylus::TransformComponent* m_Transform = nullptr;

    //Camera
    Oxylus::Ref<Oxylus::Camera> m_Camera;
    float m_TranslationDampening = 0.6f;
    float m_RotationDampening = 0.3f;
    bool m_SmoothCamera = true;
    float m_MouseSensitivity = 10.0f;
    float m_MovementSpeed = 120.0f;
    bool m_UseEditorCamera = true;
    bool m_UsingEditorCamera = false;
    glm::vec2 m_LockedMousePosition = glm::vec2(0.0f);
    glm::vec3 m_TranslationVelocity = glm::vec3(0);
    glm::vec2 m_RotationVelocity = glm::vec2(0);
  };
}
