#include "textoutput.h"
#include <moth_ui/events/event_dispatch.h>
#include <moth_ui/nodes/node_text.h>
#include <moth_ui/events/event_animation.h>

TextOutput::TextOutput(moth_ui::Context& context, std::shared_ptr<moth_ui::LayoutEntityGroup> entity)
    : Widget<TextOutput>(context, entity) {
    m_text = FindChild<moth_ui::NodeText>("text");
}

bool TextOutput::OnEvent(moth_ui::Event const& event) {
    moth_ui::EventDispatch dispatch(event);
    dispatch.Dispatch(this, &TextOutput::OnAnimationStopped);
    return dispatch.GetHandled();
}

void TextOutput::SetText(std::string_view text) {
    if (m_text) {
        m_text->SetText(text);
    }
}

void TextOutput::Flash(std::function<void()> const& onFinished) {
    SetAnimation("flash");
    m_onFlashFinished = onFinished;
}

bool TextOutput::OnAnimationStopped(moth_ui::EventAnimationStopped const& event) {
    if (m_onFlashFinished) {
        m_onFlashFinished();
        m_onFlashFinished = nullptr;
    }
    return false;
}
