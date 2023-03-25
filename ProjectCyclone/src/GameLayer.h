#pragma once
#include <Core/Layer.h>

#include "Core/Entity.h"
#include "Core/Systems/HotReloadableScenes.h"

#include "Scene/Scene.h"
#include "UI/GameUI.h"


namespace ProjectCyclone {
  using namespace Oxylus;

  class GameLayer : public Layer {
  public:
    float Time = 1;

    GameLayer();
    ~GameLayer() override;
    void OnAttach(EventDispatcher& dispatcher) override;
    void OnDetach() override;
    void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;

    static GameLayer* Get() { return s_Instance; }

  private:
    void LoadScene();
    bool OnSceneReload(ReloadSceneEvent& e);
    static void RenderFinalImage();

  private:
    static GameLayer* s_Instance;
    Ref<Scene> m_Scene;
    Entity m_CameraEntity;
    GameUI m_GameUI;
  };
}
