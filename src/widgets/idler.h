#pragma once

#include "moth_ui/nodes/widget.h"

class Idler : public moth_ui::Widget<Idler> {
public:
    inline static char const* ClassName = "idler";

    Idler(moth_ui::Context& context, std::shared_ptr<moth_ui::LayoutEntityGroup> entity);
    ~Idler() override = default;

    void Update(uint32_t ticks) override;

private:
    bool m_started = false;
};
