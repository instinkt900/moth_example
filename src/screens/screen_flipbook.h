#pragma once

#include "screen.h"

class ScreenFlipbook : public Screen {
public:
    ScreenFlipbook(moth_ui::Context& context, moth_ui::Layer const& layer);
    ~ScreenFlipbook() override;
};
