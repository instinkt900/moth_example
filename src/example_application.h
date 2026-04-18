#pragma once

#include "moth_graphics/platform/application.h"
#include <nlohmann/json.hpp>

class ExampleApplication : public moth_graphics::platform::Application
{
public:
    explicit ExampleApplication(moth_graphics::platform::IPlatform& platform);
    ~ExampleApplication() override;

    nlohmann::json& GetPersistentState() { return m_persistentState; }

private:
    void PostCreateWindow() override;

    std::filesystem::path m_imguiSettingsPath;
    std::filesystem::path m_persistentFilePath;
    nlohmann::json m_persistentState;

    static char const* const IMGUI_FILE;
    static char const* const PERSISTENCE_FILE;
};

