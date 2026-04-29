#pragma once

#include "screen.h"

class ScreenAnim : public Screen {
public:
    ScreenAnim(moth_ui::Context& context, moth_ui::Layer const& layer);
    ~ScreenAnim() override;

    bool OnEvent(moth_ui::Event const& event) override;

private:
    void OnActivate() override;
    bool OnAnimEvent(moth_ui::EventAnimation const& marker) override;

    std::shared_ptr<moth_ui::Node> m_eventNotif;
};
