#include "hittest.h"
#include <moth_ui/events/event_dispatch.h>
#include <spdlog/spdlog.h>

HitTest::HitTest(moth_ui::Context& context, std::shared_ptr<moth_ui::LayoutEntityGroup> entity)
    : Widget<HitTest>(context, entity) {
}

void HitTest::Update(uint32_t ticks) {
    if (!m_init) {
        SetAnimation("idle");
        m_init = true;
    }
    Widget::Update(ticks);
}

bool HitTest::OnEvent(moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    dispatch.Dispatch(this, &HitTest::OnMouseMove);
    dispatch.Dispatch(this, &HitTest::OnMouseDown);
    dispatch.Dispatch(this, &HitTest::OnAnimEnd);
    return dispatch.GetHandled();
}

bool HitTest::OnMouseMove(moth_ui::EventMouseMove const& event) {
    bool const wasHover = m_hover;
    m_hover = false;
    bool result = false;
    if (IsInBounds(event.GetPosition())) {
        m_hover = true;
        result = true;
    }
    if (!m_clicking) {
        if (m_hover && !wasHover) {
            SetAnimation("hover");
        } else if (!m_hover && wasHover) {
            SetAnimation("idle");
        }
    }
    return result;
}

bool HitTest::OnMouseDown(moth_ui::EventMouseDown const& event) {
    if (IsInBounds(event.GetPosition())) {
        m_clicking = true;
        SetAnimation("click");
        return true;
    }
    return false;
}

bool HitTest::OnAnimEnd(moth_ui::EventAnimationStopped const& event) {
    auto const sender = event.GetNode().lock();
    if (sender && sender.get() == this && event.GetClipName() == "click") {
        m_clicking = false;
        if (m_hover) {
            SetAnimation("hover");
        } else {
            SetAnimation("idle");
        }
    }
    return false;
}
