#pragma once

#include "moth_ui/nodes/widget.h"
#include <moth_ui/events/event_mouse.h>
#include <moth_ui/events/event_animation.h>

class HitTest : public moth_ui::Widget<HitTest> {
public:
    inline static char const* ClassName = "hittest";

    HitTest(moth_ui::Context& context, std::shared_ptr<moth_ui::LayoutEntityGroup> entity);
    ~HitTest() override = default;

    void Update(uint32_t ticks) override;
    bool OnEvent(moth_ui::Event const& event) override;

private:
    bool OnMouseMove(moth_ui::EventMouseMove const& event);
    bool OnMouseDown(moth_ui::EventMouseDown const& event);
    bool OnAnimEnd(moth_ui::EventAnimationStopped const& event);

    bool m_init = false;
    bool m_hover = false;
    bool m_clicking = false;
};
