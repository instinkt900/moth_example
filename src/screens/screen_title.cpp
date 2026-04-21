#include "screen_title.h"
#include <fmt/format.h>
#include <moth_graphics/version.h>
#include <moth_ui/nodes/node_text.h>
#include <moth_ui/version.h>

ScreenTitle::ScreenTitle(moth_ui::Context& context, moth_ui::Layer const& layer)
    : Screen(context, layer, "assets/layouts/screens/title.mothui", "") {
    if (m_root) {
        if (auto node = m_root->FindChild<moth_ui::NodeText>("moth_ui_version")) {
            node->SetText(fmt::format("moth_ui version: {}", moth_ui::Version));
        }

        if (auto node = m_root->FindChild<moth_ui::NodeText>("moth_graphics_version")) {
            node->SetText(fmt::format("moth_graphics version: {}", moth_graphics::Version));
        }
    }
}

ScreenTitle::~ScreenTitle() = default;

