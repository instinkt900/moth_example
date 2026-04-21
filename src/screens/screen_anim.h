#pragma once

#include "screen.h"

class ScreenAnim : public Screen {
public:
    ScreenAnim(moth_ui::Context& context, moth_ui::Layer const& layer);
    ~ScreenAnim() override;

private:
    void OnActivate() override;
};
