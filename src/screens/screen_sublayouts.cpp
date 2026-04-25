#include "screen_sublayouts.h"

ScreenSublayouts::ScreenSublayouts(moth_ui::Context& context, moth_ui::Layer const& layer)
    : Screen(context, layer, "assets/layouts/screens/sublayouts.mothui", "Sublayout references") {
}

ScreenSublayouts::~ScreenSublayouts() = default;

