#include "FreeCamera.h"

namespace ProjectCyclone {
  using namespace Oxylus;

  void FreeCamera::OnCreate() {
    m_Camera = GetComponent<CameraComponent>().System;
    m_Transform = &GetComponent<TransformComponent>();
  }

  void FreeCamera::OnUpdate(float deltaTime) {
    ZoneScoped;
    auto& Camera = *m_Camera;
    const glm::vec3& position = Camera.GetPosition();
    const glm::vec2 yawPitch = glm::vec2(Camera.GetYaw(), Camera.GetPitch());
    glm::vec3 finalPosition = position;
    glm::vec2 finalYawPitch = yawPitch;

    if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
      ImGui::SetMouseCursor(ImGuiMouseCursor_None);
      const glm::vec2 newMousePosition = Input::GetMousePosition();

      if (!m_UsingEditorCamera) {
        m_UsingEditorCamera = true;
        m_LockedMousePosition = newMousePosition;
      }

      Input::SetCursorPosition(m_LockedMousePosition.x, m_LockedMousePosition.y);

      const glm::vec2 change = (newMousePosition - m_LockedMousePosition) * m_MouseSensitivity * deltaTime;
      finalYawPitch.x += change.x;
      finalYawPitch.y = glm::clamp(finalYawPitch.y - change.y, -89.9f, 89.9f);

      const float maxMoveSpeed = m_MovementSpeed * (ImGui::IsKeyDown(ImGuiKey_LeftShift) ? 3.0f : 1.0f) * deltaTime;
      if (ImGui::IsKeyDown(ImGuiKey_W))
        finalPosition += Camera.GetFront() * maxMoveSpeed;
      else if (ImGui::IsKeyDown(ImGuiKey_S))
        finalPosition -= Camera.GetFront() * maxMoveSpeed;
      if (ImGui::IsKeyDown(ImGuiKey_D))
        finalPosition += Camera.GetRight() * maxMoveSpeed;
      else if (ImGui::IsKeyDown(ImGuiKey_A))
        finalPosition -= Camera.GetRight() * maxMoveSpeed;

      if (ImGui::IsKeyDown(ImGuiKey_Q)) {
        finalPosition.y -= maxMoveSpeed;
      }
      else if (ImGui::IsKeyDown(ImGuiKey_E)) {
        finalPosition.y += maxMoveSpeed;
      }
    }
    else {
      m_UsingEditorCamera = false;
    }

    const glm::vec3 dampedPosition = Math::SmoothDamp(position,
                                                      finalPosition,
                                                      m_TranslationVelocity,
                                                      m_TranslationDampening,
                                                      10000.0f,
                                                      deltaTime);
    const glm::vec2 dampedYawPitch = Math::SmoothDamp(yawPitch,
                                                      finalYawPitch,
                                                      m_RotationVelocity,
                                                      m_RotationDampening,
                                                      1000.0f,
                                                      deltaTime);
    m_Transform->Translation = m_SmoothCamera ? dampedPosition : finalPosition;
    m_Transform->Rotation.x = m_SmoothCamera ? dampedYawPitch.y : finalYawPitch.y;
    m_Transform->Rotation.y = m_SmoothCamera ? dampedYawPitch.x : finalYawPitch.x;
  }

  void FreeCamera::OnDestroy() { }
}
