#include "chrome_layer.h"
#include "events.h"
#include "widgets/ui_button.h"
#include <moth_ui/moth_ui.h>

ChromeLayer::ChromeLayer(moth_ui::Context& context)
    : m_context(context) {
    m_root = moth_ui::NodeFactory::Get().Create(m_context, "assets/layouts/chrome.mothui", GetWidth(), GetHeight());
    m_root->SetEventHandler([this](moth_ui::Node* node, moth_ui::Event const& event) {
        return LayoutEvent(node, event);
    });

    auto nextButton = m_root->FindChild<UIButton>("next_button");
    auto prevButton = m_root->FindChild<UIButton>("prev_button");

    if (nextButton) {
        nextButton->SetClickAction([&]() {
                m_layerStack->FireEvent(EventNextPage{});
        });
    }
    if (prevButton) {
        prevButton->SetClickAction([&]() {
                m_layerStack->FireEvent(EventPrevPage{});
        });
    }
}

bool ChromeLayer::OnEvent(moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    bool handled = dispatch.GetHandled();
    if (!handled && m_root) {
        handled = m_root->SendEvent(event, moth_ui::Node::EventDirection::Down);
    }
    return dispatch.GetHandled();
}

void ChromeLayer::Update(uint32_t ticks) {
    if (m_root) {
        m_root->Update(ticks);
    }
}

void ChromeLayer::Draw() {
    if (m_root) {
        moth_ui::IntVec2 const displaySize{ GetWidth(), GetHeight() };
        auto const currentSize = m_root->GetScreenRect().dimensions();
        if (currentSize != displaySize) {
            moth_ui::IntRect displayRect;
            displayRect.topLeft = { 0, 0 };
            displayRect.bottomRight = displaySize;
            m_root->SetScreenRect(displayRect);
        }
    }
    if (m_root) {
        m_root->Draw();
    }
}

void ChromeLayer::OnAddedToStack(moth_ui::LayerStack* stack) {
    Layer::OnAddedToStack(stack);
    if (m_root) {
        moth_ui::IntRect rect;
        rect.topLeft = { 0, 0 };
        rect.bottomRight = { GetWidth(), GetHeight() };
        m_root->SetScreenRect(rect);
    }
}

void ChromeLayer::OnRemovedFromStack() {
    Layer::OnRemovedFromStack();
}

bool ChromeLayer::LayoutEvent(moth_ui::Node* node, moth_ui::Event const& event) {
    return false;
}
