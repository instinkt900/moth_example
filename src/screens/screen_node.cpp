#include "screen_node.h"

ScreenNode::ScreenNode(moth_ui::Context& context, moth_ui::Layer const& layer)
    : Screen(context, layer, "assets/layouts/screens/nodes.mothui", "Basic Node Types") {
}

ScreenNode::~ScreenNode() = default;

