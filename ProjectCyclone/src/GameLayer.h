#pragma once
#include <Core/Layer.h>

#include "Core/Entity.h"
#include "Core/Systems/HotReloadableScenes.h"

#include "Scene/Scene.h"


namespace ProjectCyclone {
  using namespace Oxylus;

  class GameLayer : public Layer {
  public:
    ~GameLayer() override;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float DeltaTime) override;
    void OnImGuiRender() override;

    void OnEvent(Event& e) override;

  private:
    void LoadScene();
    bool OnSceneReload(ReloadSceneEvent& e);
    static void RenderFinalImage();

  private:
    Ref<Scene> m_Scene;
    Entity m_CameraEntity;
  };
}
