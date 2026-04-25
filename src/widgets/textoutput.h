#pragma once

#include "moth_ui/nodes/widget.h"

class TextOutput : public moth_ui::Widget<TextOutput> {
public:
    inline static char const* ClassName = "textoutput";

    TextOutput(moth_ui::Context& context, std::shared_ptr<moth_ui::LayoutEntityGroup> entity);
    ~TextOutput() override = default;

    bool OnEvent(moth_ui::Event const& event) override;

    void SetText(std::string_view text);
    void Flash(std::function<void()> const& onFinished);

private:
    std::shared_ptr<moth_ui::NodeText> m_text;
    std::function<void()> m_onFlashFinished;

    bool OnAnimationStopped(moth_ui::EventAnimationStopped const& event);
};
