#include "screen_flipbook.h"
#include "widgets/ui_button.h"
#include <moth_ui/nodes/node_flipbook.h>

ScreenFlipbook::ScreenFlipbook(moth_ui::Context& context, moth_ui::Layer const& layer)
    : Screen(context, layer, "assets/layouts/screens/flipbook.mothui", "Flipbook animations") {
    auto idleButton = m_root->FindChild<UIButton>("btn_idle");
    auto runButton = m_root->FindChild<UIButton>("btn_run");
    auto spriteNode = m_root->FindChild("sprite");

    if (spriteNode) {
        if (idleButton) {
            idleButton->SetClickAction([spriteNode]() {
                spriteNode->SetAnimation("idle");
            });
        }
        if (runButton) {
            runButton->SetClickAction([spriteNode]() {
                spriteNode->SetAnimation("run");
            });
        }
    }
}

ScreenFlipbook::~ScreenFlipbook() = default;

