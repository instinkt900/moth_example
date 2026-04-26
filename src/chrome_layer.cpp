#include "chrome_layer.h"
#include "events.h"
#include "example_layer.h"
#include "widgets/ui_button.h"
#include <moth_ui/moth_ui.h>
#include <spdlog/spdlog.h>

ChromeLayer::ChromeLayer(moth_ui::Context& context, ExampleLayer const& displayLayer)
    : m_context(context)
    , m_displayLayer(displayLayer) {
    m_root = moth_ui::NodeFactory::Get().Create(m_context, "assets/layouts/chrome.mothui", GetWidth(), GetHeight());
    m_root->SetEventHandler([this](moth_ui::Node* node, moth_ui::Event const& event) {
        return LayoutEvent(node, event);
    });

    m_titleNode = m_root->FindChild<moth_ui::NodeText>("screen_title");
    if (m_titleNode) {
        m_titleNode->SetText("");
    }

    auto nextButton = m_root->FindChild<UIButton>("next_button");
    auto prevButton = m_root->FindChild<UIButton>("prev_button");

    if (nextButton) {
        nextButton->SetClickAction([&]() {
            FireEvent(EventNextPage{});
        });
    }
    if (prevButton) {
        prevButton->SetClickAction([&]() {
            FireEvent(EventPrevPage{});
        });
    }

    m_dots.resize(m_displayLayer.GetNumPages());
    for (auto i = 0; i < m_dots.size(); ++i) {
        m_dots[i] = m_root->FindChild(fmt::format("dot_{:02d}", i+1));
    }
}

bool ChromeLayer::OnEvent(moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    dispatch.Dispatch(this, &ChromeLayer::OnPageChanged);
    bool handled = dispatch.GetHandled();
    if (!handled && m_root) {
        handled = m_root->Broadcast(event);
    }
    return handled;
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
    OnPageChanged(EventPageChanged{});
}

void ChromeLayer::OnRemovedFromStack() {
    Layer::OnRemovedFromStack();
}

bool ChromeLayer::LayoutEvent(moth_ui::Node* node, moth_ui::Event const& event) {
    return false;
}

bool ChromeLayer::OnPageChanged(EventPageChanged const& event) {
    if (m_titleNode) {
        m_titleNode->SetText(m_displayLayer.GetPageTitle());
    }
    auto const index = m_displayLayer.GetCurPageNo();
    for (auto i = 0; i < m_dots.size(); ++i) {
        auto& dot = m_dots[i];
        if (dot) {
            dot->SetAnimation(i == index ? "high" : "low");
        }
    }
    return true;
}
