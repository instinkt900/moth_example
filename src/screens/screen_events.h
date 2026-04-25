#pragma once

#include "screen.h"
#include "widgets/textoutput.h"

class ScreenEvents : public Screen {
public:
    ScreenEvents(moth_ui::Context& context, moth_ui::Layer const& layer);
    ~ScreenEvents() override;

    bool OnEvent(moth_ui::Event const& event) override;

private:
    std::shared_ptr<TextOutput> m_mouseCoords;
    std::shared_ptr<TextOutput> m_keyboardInput;

    std::string m_keyBuffer;

    bool OnMouseMove(moth_ui::EventMouseMove const& event);
    bool OnKey(moth_ui::EventKey const& event);
};
