#include "idler.h"

Idler::Idler(moth_ui::Context& context, std::shared_ptr<moth_ui::LayoutEntityGroup> entity)
    : Widget<Idler>(context, entity) {
}

void Idler::Update(uint32_t ticks) {
    if (!m_started) {
        SetAnimation("idle");
        m_started = true;
    }
    Widget::Update(ticks);
}
