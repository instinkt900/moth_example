#include "screen.h"
#include <fmt/format.h>
#include <moth_ui/events/event_animation.h>
#include <moth_ui/events/event_dispatch.h>
#include <moth_ui/layers/layer.h>
#include <moth_ui/node_factory.h>
#include <moth_ui/nodes/node_text.h>
#include <moth_ui/version.h>
#include <moth_graphics/version.h>
#include <spdlog/spdlog.h>

static const std::string_view ActivateAnimName = "activate";
static const std::string_view DeactivateAnimName = "deactivate";
static const std::string_view IdleAnimName = "idle";

Screen::Screen(moth_ui::Context& context, moth_ui::Layer const& layer, std::string_view layoutPath, std::string_view title)
    : m_context(context)
    , m_title(title) {
    auto [node, result] = moth_ui::NodeFactory::Get().Create(m_context, layoutPath, layer.GetWidth(), layer.GetHeight());
    m_root = node; // NOLINT(cppcoreguidelines-prefer-member-initializer)
    if (m_root) {
        m_root->SetEventHandler([this](moth_ui::Node* node, moth_ui::Event const& event) {
            return LayoutEvent(node, event);
        });
    }
}

Screen::~Screen() = default;

void Screen::Activate() {
    if (m_root) {
        m_root->SetAnimation(ActivateAnimName);
    }
}

void Screen::Deactivate(std::function<void()> const& onComplete) {
    m_deactivateAction = onComplete;
    if (m_root && m_root->HasAnimation(DeactivateAnimName)) {
        m_root->SetAnimation(DeactivateAnimName);
    } else {
        m_deactivateAction();
    }
}

bool Screen::OnEvent(moth_ui::Event const& event) {
    bool result = false;
    if (m_root) {
        result = m_root->Broadcast(event);
    }
    return result;
}

void Screen::Update(uint32_t ticks) {
    if (m_root) {
        auto rootCopy = m_root;
        rootCopy->Update(ticks);
    }
}

void Screen::Draw() {
    if (m_root) {
        m_root->Draw();
    }
}

bool Screen::LayoutEvent(moth_ui::Node* node, moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    dispatch.Dispatch(this, &Screen::OnAnimationStopped);
    dispatch.Dispatch(this, &Screen::OnAnimEvent);
    return dispatch.GetHandled();
}

bool Screen::OnAnimationStopped(moth_ui::EventAnimationStopped const& event) {
    if (event.GetClipName() == ActivateAnimName) {
        if (m_root) {
            m_root->SetAnimation(IdleAnimName);
            OnActivate();
        }
        return true;
    }
    if (event.GetClipName() == DeactivateAnimName) {
        OnDeactivate();
        if (m_deactivateAction) {
            m_deactivateAction();
        }
        return true;
    }
    return false;
}
