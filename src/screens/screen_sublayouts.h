#pragma once

#include "screen.h"

class ScreenSublayouts : public Screen {
public:
    ScreenSublayouts(moth_ui::Context& context, moth_ui::Layer const& layer);
    ~ScreenSublayouts() override;
};
