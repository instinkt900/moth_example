#include "screen_anim.h"
#include <moth_ui/events/event_dispatch.h>
#include <moth_ui/events/event_animation.h>
#include <spdlog/spdlog.h>

ScreenAnim::ScreenAnim(moth_ui::Context& context, moth_ui::Layer const& layer)
    : Screen(context, layer, "assets/layouts/screens/animation.mothui", "Animation Easings") {
    m_eventNotif = m_root->FindChild("event_notif");
}

ScreenAnim::~ScreenAnim() = default;

bool ScreenAnim::OnEvent(moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    dispatch.Dispatch(this, &ScreenAnim::OnAnimEvent);
    return dispatch.GetHandled() || Screen::OnEvent(event);
}

void ScreenAnim::OnActivate() {
    if (auto rack = m_root->FindChild("anim_table")) {
        rack->SetAnimation("idle");
    }
}

bool ScreenAnim::OnAnimEvent(moth_ui::EventAnimation const& marker) {
    if (marker.GetName() == "event01" && m_eventNotif) {
        m_eventNotif->SetAnimation("event");
    }
    return false;
}


