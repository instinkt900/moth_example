#pragma once

#include <moth_graphics/events/canyon_events.h>
#include <moth_ui/events/event.h>

enum ExampleEventType : int {
    EVENTTYPE_NEXTPAGE = moth_graphics::EVENTTYPE_GRAPHICSUSER0,
    EVENTTYPE_PREVPAGE,
};

class EventNextPage : public moth_ui::Event {
public:
    EventNextPage()
        : Event(GetStaticType()) {}
    ~EventNextPage() override = default;

    static constexpr int GetStaticType() { return EVENTTYPE_NEXTPAGE; }

    std::unique_ptr<Event> Clone() const override {
        return std::make_unique<EventNextPage>();
    }
};

class EventPrevPage : public moth_ui::Event {
public:
    EventPrevPage()
        : Event(GetStaticType()) {}
    ~EventPrevPage() override = default;

    static constexpr int GetStaticType() { return EVENTTYPE_PREVPAGE; }

    std::unique_ptr<Event> Clone() const override {
        return std::make_unique<EventNextPage>();
    }
};
