#include "GameLayer.h"

#include <OxylusEngine.h>
#include <Core/EntryPoint.h>
#include <Core/Project.h>
#include <Core/Systems/HotReloadableScenes.h>

namespace Oxylus {
  class ProjectCyclone : public Application {
  public:
    ProjectCyclone(const AppSpec& spec) : Application(spec) { }
  };

  Application* CreateApplication(ApplicationCommandLineArgs args) {
    AppSpec spec;
    spec.Name = "ProjectCyclone";

    spec.Backend = Core::RenderBackend::Vulkan;
    spec.WorkingDirectory = std::filesystem::current_path().string();
    spec.CommandLineArgs = args;
    spec.CustomWindowTitle = false;
    spec.UseImGui = true;

    const auto app = new ProjectCyclone(spec);
    app->PushLayer(new ::ProjectCyclone::GameLayer())
        .AddSystem<HotReloadableScenes>("Assets/Scenes/Main.oxscene");

    return app;
  }
}
