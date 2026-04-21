#pragma once

#include "iscreen.h"

class Screen : public IScreen {
public:
    Screen(moth_ui::Context& context, moth_ui::Layer const& layer, std::string_view layoutPath, std::string_view title);
    ~Screen() override;

    void Activate() override;
    void Deactivate(std::function<void()> const& onComplete) override;

    void Update(uint32_t ticks) override;
    void Draw() override;

    std::shared_ptr<moth_ui::Group> GetRoot() override { return m_root; }

    std::string_view GetTitle() const override { return m_title; }

protected:
    moth_ui::Context& m_context;
    std::shared_ptr<moth_ui::Group> m_root;
    std::string m_title;

    virtual void OnActivate() {}
    virtual void OnDeactivate() {}

private:
    std::function<void()> m_deactivateAction;

    bool LayoutEvent(moth_ui::Node* node, moth_ui::Event const& event);
    bool OnAnimationStopped(moth_ui::EventAnimationStopped const& event);
};
