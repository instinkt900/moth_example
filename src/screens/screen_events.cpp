#include "screen_events.h"
#include <fmt/format.h>
#include <moth_ui/events/event_dispatch.h>
#include <moth_ui/events/event_key.h>
#include <moth_ui/events/event_mouse.h>

char KeyToChar(moth_ui::EventKey const& event) {
    switch (event.GetKey()) {
    case moth_ui::Key::A:
        return 'a';
    case moth_ui::Key::B:
        return 'b';
    case moth_ui::Key::C:
        return 'c';
    case moth_ui::Key::D:
        return 'd';
    case moth_ui::Key::E:
        return 'e';
    case moth_ui::Key::F:
        return 'f';
    case moth_ui::Key::G:
        return 'g';
    case moth_ui::Key::H:
        return 'h';
    case moth_ui::Key::I:
        return 'i';
    case moth_ui::Key::J:
        return 'j';
    case moth_ui::Key::K:
        return 'k';
    case moth_ui::Key::L:
        return 'l';
    case moth_ui::Key::M:
        return 'm';
    case moth_ui::Key::N:
        return 'n';
    case moth_ui::Key::O:
        return 'o';
    case moth_ui::Key::P:
        return 'p';
    case moth_ui::Key::Q:
        return 'q';
    case moth_ui::Key::R:
        return 'r';
    case moth_ui::Key::S:
        return 's';
    case moth_ui::Key::T:
        return 't';
    case moth_ui::Key::U:
        return 'u';
    case moth_ui::Key::V:
        return 'v';
    case moth_ui::Key::W:
        return 'w';
    case moth_ui::Key::X:
        return 'x';
    case moth_ui::Key::Y:
        return 'y';
    case moth_ui::Key::Z:
        return 'z';
    case moth_ui::Key::N0:
        return '0';
    case moth_ui::Key::N1:
        return '1';
    case moth_ui::Key::N2:
        return '2';
    case moth_ui::Key::N3:
        return '3';
    case moth_ui::Key::N4:
        return '4';
    case moth_ui::Key::N5:
        return '5';
    case moth_ui::Key::N6:
        return '6';
    case moth_ui::Key::N7:
        return '7';
    case moth_ui::Key::N8:
        return '8';
    case moth_ui::Key::N9:
        return '9';
    default:
        return ' ';
    };
}

ScreenEvents::ScreenEvents(moth_ui::Context& context, moth_ui::Layer const& layer)
    : Screen(context, layer, "assets/layouts/screens/events.mothui", "Events") {
    m_mouseCoords = m_root->FindChild<TextOutput>("mouse_coords");
    m_keyboardInput = m_root->FindChild<TextOutput>("keyboard_input");
    m_mouseCoords->SetText("");
    m_keyboardInput->SetText("");
}

ScreenEvents::~ScreenEvents() = default;

bool ScreenEvents::OnEvent(moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    dispatch.Dispatch(this, &ScreenEvents::OnMouseMove);
    dispatch.Dispatch(this, &ScreenEvents::OnKey);
    return dispatch.GetHandled() || Screen::OnEvent(event);
}

bool ScreenEvents::OnMouseMove(moth_ui::EventMouseMove const& event) {
    if (m_mouseCoords) {
        m_mouseCoords->SetText(fmt::format("{},{}", event.GetPosition().x, event.GetPosition().y));
    }
    return false;
}

bool ScreenEvents::OnKey(moth_ui::EventKey const& event) {
    if (event.GetAction() == moth_ui::KeyAction::Down) {
        if (m_keyboardInput) {
            m_keyBuffer += KeyToChar(event);
            m_keyboardInput->SetText(m_keyBuffer);
            m_keyboardInput->Flash([this]() { m_keyBuffer.clear(); });
        }
    }
    return false;
}
