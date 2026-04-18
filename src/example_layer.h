#pragma once

#include "screens/iscreen.h"
#include <moth_ui/moth_ui_fwd.h>
#include <moth_ui/layers/layer.h>
#include <moth_ui/utils/vector.h>
#include <moth_graphics/events/event_window.h>

class ExampleLayer : public moth_ui::Layer {
public:
    ExampleLayer(moth_ui::Context& context);
    ~ExampleLayer() override = default;
    
    bool OnEvent(moth_ui::Event const& event) override;
    void Update(uint32_t ticks) override;
    void Draw() override;

    void OnAddedToStack(moth_ui::LayerStack* stack) override;
    void OnRemovedFromStack() override;

protected:
    moth_ui::Context& m_context;
    std::shared_ptr<moth_ui::Group> m_root;

    bool OnRequestQuitEvent(moth_graphics::EventRequestQuit const& event);

private:
    std::unique_ptr<IScreen> MakeScreen(int index);
    void LoadScreen(int index);

    std::unique_ptr<IScreen> m_currentScreen;
};
