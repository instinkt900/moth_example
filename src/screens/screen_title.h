#pragma once

#include "iscreen.h"

class ScreenTitle : public IScreen {
public:
    ScreenTitle(moth_ui::Context& context, moth_ui::Layer const& layer);
    ~ScreenTitle() override;

    void Activate() override;
    void Deactivate(std::function<void()> const& onComplete) override;

    void Update(uint32_t ticks) override;
    void Draw() override;

    std::shared_ptr<moth_ui::Group> GetRoot() override { return m_root; }

private:
    moth_ui::Context& m_context;
    std::shared_ptr<moth_ui::Group> m_root;
    std::function<void()> m_deactivateAction;

    bool LayoutEvent(moth_ui::Node* node, moth_ui::Event const& event);
    bool OnAnimationStopped(moth_ui::EventAnimationStopped const& event);
};
