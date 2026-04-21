#include "screen_anim.h"

ScreenAnim::ScreenAnim(moth_ui::Context& context, moth_ui::Layer const& layer)
    : Screen(context, layer, "assets/layouts/screens/animation.mothui", "Animation Easings") {
}

ScreenAnim::~ScreenAnim() = default;

void ScreenAnim::OnActivate() {
    if (auto rack = m_root->FindChild("anim_table")) {
        rack->SetAnimation("idle");
    }
}

