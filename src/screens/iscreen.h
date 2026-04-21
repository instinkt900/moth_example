#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <moth_ui/nodes/group.h>

class IScreen {
public:
    virtual ~IScreen() = default;

    virtual void Activate() = 0;
    virtual void Deactivate(std::function<void()> const& onComplete) = 0;

    virtual void Update(uint32_t ticks) = 0;
    virtual void Draw() = 0;

    virtual std::shared_ptr<moth_ui::Group> GetRoot() = 0;

    virtual std::string_view GetTitle() const = 0;
};
