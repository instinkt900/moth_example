#pragma once

#include <moth_ui/moth_ui_fwd.h>
#include <moth_ui/layers/layer.h>
#include <moth_ui/utils/vector.h>
#include <moth_graphics/events/event_window.h>

class ChromeLayer : public moth_ui::Layer {
public:
    ChromeLayer(moth_ui::Context& context);
    ~ChromeLayer() override = default;
    
    bool OnEvent(moth_ui::Event const& event) override;
    void Update(uint32_t ticks) override;
    void Draw() override;

    void OnAddedToStack(moth_ui::LayerStack* stack) override;
    void OnRemovedFromStack() override;

protected:
    moth_ui::Context& m_context;
    std::shared_ptr<moth_ui::Group> m_root;

    bool LayoutEvent(moth_ui::Node* node, moth_ui::Event const& event);
};
