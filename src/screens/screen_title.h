#pragma once

#include "screen.h"

class ScreenTitle : public Screen {
public:
    ScreenTitle(moth_ui::Context& context, moth_ui::Layer const& layer);
    ~ScreenTitle() override;
};
