#pragma once

#include "screen.h"

class ScreenNode : public Screen {
public:
    ScreenNode(moth_ui::Context& context, moth_ui::Layer const& layer);
    ~ScreenNode() override;
};
