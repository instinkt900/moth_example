#include "example_layer.h"
#include "screens/screen_anim.h"
#include "screens/screen_node.h"
#include "screens/screen_title.h"

#include <moth_ui/moth_ui.h>

using ScreenCtor = std::unique_ptr<IScreen> (*)(moth_ui::Context&, moth_ui::Layer const&);
template <typename T>
std::unique_ptr<IScreen> MakeScreenOf(moth_ui::Context& ctx, moth_ui::Layer const& layer) {
    return std::make_unique<T>(ctx, layer);
}

static constexpr std::array<ScreenCtor, 3> screens = { {
    &MakeScreenOf<ScreenTitle>,
    &MakeScreenOf<ScreenNode>,
    &MakeScreenOf<ScreenAnim>,
} };

ExampleLayer::ExampleLayer(moth_ui::Context& context)
    : m_context(context) {
}

bool ExampleLayer::OnEvent(moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    dispatch.Dispatch(this, &ExampleLayer::OnRequestQuitEvent);
    dispatch.Dispatch(this, &ExampleLayer::OnKeyEvent);
    dispatch.Dispatch(this, &ExampleLayer::OnNextPageEvent);
    dispatch.Dispatch(this, &ExampleLayer::OnPrevPageEvent);
    bool handled = dispatch.GetHandled();
    if (!handled && m_root) {
        handled = m_root->SendEvent(event, moth_ui::Node::EventDirection::Down);
    }
    return handled;
}

void ExampleLayer::Update(uint32_t ticks) {
    if (m_currentScreen) {
        m_currentScreen->Update(ticks);
    }
}

void ExampleLayer::Draw() {
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
    if (m_currentScreen) {
        m_currentScreen->Draw();
    }
}

void ExampleLayer::OnAddedToStack(moth_ui::LayerStack* stack) {
    Layer::OnAddedToStack(stack);
    LoadScreen(0);
    if (m_root) {
        moth_ui::IntRect rect;
        rect.topLeft = { 0, 0 };
        rect.bottomRight = { GetWidth(), GetHeight() };
        m_root->SetScreenRect(rect);
    }
    stack->SetEventListener(this);
}

void ExampleLayer::OnRemovedFromStack() {
    Layer::OnRemovedFromStack();
}

std::string_view ExampleLayer::GetPageTitle() const {
    if (m_currentScreen) {
        return m_currentScreen->GetTitle();
    }
    return "";
}

bool ExampleLayer::OnRequestQuitEvent(moth_graphics::EventRequestQuit const& event) {
    m_layerStack->FireEvent(moth_graphics::EventQuit());
    return true;
}

bool ExampleLayer::OnKeyEvent(moth_ui::EventKey const& event) {
    if (event.GetAction() == moth_ui::KeyAction::Down && event.GetKey() == moth_ui::Key::Escape) {
        m_layerStack->FireEvent(moth_graphics::EventQuit());
        return true;
    }
    return false;
}

bool ExampleLayer::OnNextPageEvent(EventNextPage const& event) {
    LoadScreen(m_currentIndex + 1);
    return true;
}

bool ExampleLayer::OnPrevPageEvent(EventPrevPage const& event) {
    LoadScreen(m_currentIndex - 1);
    return true;
}

std::unique_ptr<IScreen> ExampleLayer::MakeScreen(int index) {
    auto const ctor = screens.at(std::clamp<int>(index, 0, screens.size() - 1));
    return ctor(m_context, *this);
}

void ExampleLayer::LoadScreen(int index) {
    m_currentIndex = std::clamp<int>(index, 0, screens.size() - 1);
    if (m_currentScreen) {
        m_currentScreen->Deactivate([this]() { m_currentScreen = nullptr; LoadScreen(m_currentIndex); });
    } else {
        m_currentScreen = MakeScreen(m_currentIndex);
        m_root = m_currentScreen->GetRoot();
        m_layerStack->FireEvent(EventPageChanged{});
        m_currentScreen->Activate();
    }
}
