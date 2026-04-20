#include "screen_node.h"
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

ScreenNode::ScreenNode(moth_ui::Context& context, moth_ui::Layer const& layer)
    : m_context(context) {
    m_root = moth_ui::NodeFactory::Get().Create(m_context, "assets/layouts/screens/nodes.mothui", layer.GetWidth(), layer.GetHeight());
    if (m_root) {
        m_root->SetEventHandler([this](moth_ui::Node* node, moth_ui::Event const& event) {
            return LayoutEvent(node, event);
        });
    }
}

ScreenNode::~ScreenNode() = default;

void ScreenNode::Activate() {
    if (m_root) {
        m_root->SetAnimation(ActivateAnimName);
    }
}

void ScreenNode::Deactivate(std::function<void()> const& onComplete) {
    if (m_root) {
        m_deactivateAction = onComplete;
        m_root->SetAnimation(DeactivateAnimName);
    } else {
        m_deactivateAction();
    }
}

void ScreenNode::Update(uint32_t ticks) {
    if (m_root) {
        auto rootCopy = m_root;
        rootCopy->Update(ticks);
    }
}

void ScreenNode::Draw() {
    if (m_root) {
        m_root->Draw();
    }
}

bool ScreenNode::LayoutEvent(moth_ui::Node* node, moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    dispatch.Dispatch(this, &ScreenNode::OnAnimationStopped);
    return dispatch.GetHandled();
}

bool ScreenNode::OnAnimationStopped(moth_ui::EventAnimationStopped const& event) {
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
