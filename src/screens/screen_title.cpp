#include "screen_title.h"
#include <fmt/format.h>
#include <moth_ui/events/event_animation.h>
#include <moth_ui/events/event_dispatch.h>
#include <moth_ui/layers/layer.h>
#include <moth_ui/node_factory.h>
#include <moth_ui/nodes/node_text.h>
#include <moth_ui/version.h>
#include <moth_graphics/version.h>

static const std::string_view ActivateAnimName = "activate";
static const std::string_view DeactivateAnimName = "deactivate";
static const std::string_view IdleAnimName = "idle";

ScreenTitle::ScreenTitle(moth_ui::Context& context, moth_ui::Layer const& layer)
    : m_context(context) {
    m_root = moth_ui::NodeFactory::Get().Create(m_context, "assets/layouts/screens/title.mothui", layer.GetWidth(), layer.GetHeight());
    if (m_root) {
        m_root->SetEventHandler([this](moth_ui::Node* node, moth_ui::Event const& event) {
            return LayoutEvent(node, event);
        });

        if (auto node = m_root->FindChild<moth_ui::NodeText>("moth_ui_version")) {
            node->SetText(fmt::format("moth_ui version: {}", moth_ui::Version));
        }

        if (auto node = m_root->FindChild<moth_ui::NodeText>("moth_graphics_version")) {
            node->SetText(fmt::format("moth_graphics version: {}", moth_graphics::Version));
        }
    }
}

ScreenTitle::~ScreenTitle() = default;

void ScreenTitle::Activate() {
    if (m_root) {
        m_root->SetAnimation(ActivateAnimName);
    }
}

void ScreenTitle::Deactivate(std::function<void()> const& onComplete) {
    if (m_root) {
        m_deactivateAction = onComplete;
        m_root->SetAnimation(DeactivateAnimName);
    } else {
        m_deactivateAction();
    }
}

void ScreenTitle::Update(uint32_t ticks) {
    if (m_root) {
        m_root->Update(ticks);
    }
}

void ScreenTitle::Draw() {
    if (m_root) {
        m_root->Draw();
    }
}

bool ScreenTitle::LayoutEvent(moth_ui::Node* node, moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    dispatch.Dispatch(this, &ScreenTitle::OnAnimationStopped);
    return dispatch.GetHandled();
}

bool ScreenTitle::OnAnimationStopped(moth_ui::EventAnimationStopped const& event) {
    if (event.GetClipName() == ActivateAnimName) {
        if (m_root) {
            m_root->SetAnimation(IdleAnimName);
        }
        return true;
    }
    if (event.GetClipName() == DeactivateAnimName) {
        if (m_deactivateAction) {
            m_deactivateAction();
        }
        return true;
    }
    return false;
}
