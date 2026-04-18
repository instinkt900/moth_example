#include "example_application.h"
#include <moth_graphics/platform/sdl/sdl_platform.h>
#include <moth_graphics/platform/glfw/glfw_platform.h>

int main(int argc, char** argv) {
    bool useVulkan = false;
    for (int i = 1; i < argc; ++i) {
        std::string_view const arg(argv[i]);
        if (arg == "--vulkan") { useVulkan = true; }
    }

    std::unique_ptr<moth_graphics::platform::IPlatform> platform;
    if (useVulkan) {
        platform = std::make_unique<moth_graphics::platform::glfw::Platform>();
    } else {
        platform = std::make_unique<moth_graphics::platform::sdl::Platform>();
    }

    platform->Startup();
    ExampleApplication application(*platform);
    application.Init();
    application.Run();
    platform->Shutdown();
}
