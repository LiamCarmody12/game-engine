/**
 * @file engine/src/core/events/MouseEvent.h
 * @brief All events related mouse input.
 */
#ifndef ENGINE_SRC_CORE_EVENTS_MOUSEEVENT_H_
#define ENGINE_SRC_CORE_EVENTS_MOUSEEVENT_H_

#include <sstream>

#include "Event.h"

namespace engine {
namespace events {

/**
 * @class MouseMovedEvent
 * @brief Generated whenever the user moves their mouse within the application.
 */
class ENGINE_API MouseMovedEvent : public Event {
 public:
  MouseMovedEvent(float x, float y) : mouse_x_(x), mouse_y_(y) {}

  inline float GetX() const { return mouse_x_; }
  inline float GetY() const { return mouse_y_; }

  std::string ToString() const override {
    std::stringstream event_string;
    event_string << "MouseMovedEvent: " << GetX() << ", " << GetY();
    return event_string.str();
  }

  EVENT_CLASS_TYPE(kMouseMoved)
  EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)
 private:
  float mouse_x_, mouse_y_;
};

/**
 * @class MouseScrolledEvent
 * @brief Generated whenever the user scrolls their mouse wheel within the
 * application.
 */
class ENGINE_API MouseScrolledEvent : public Event {
 public:
  MouseScrolledEvent(float x_offset, float y_offset)
      : x_offset_(x_offset), y_offset_(y_offset) {}

  inline float GetXOffset() const { return x_offset_; }
  inline float GetYOffset() const { return y_offset_; }

  std::string ToString() const override {
    std::stringstream event_string;
    event_string
        << "MouseScrolledEvent: "
        << GetXOffset()
        << ", "
        << GetYOffset();
    return event_string.str();
  }

  EVENT_CLASS_TYPE(kMouseScrolled)
  EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)
 private:
  float x_offset_, y_offset_;
};

/**
 * @class MouseButtonEvent
 * @brief The generic Mouse button event.
 */
class ENGINE_API MouseButtonEvent : public Event {
 public:
  inline int GetMouseButton() const { return button_; }

  EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)

 protected:
  explicit MouseButtonEvent(int button) : button_(button) {}
  int button_;
};

/**
 * @class MouseButtonPressedEvent
 * @brief Generated whenever the user presses a mouse button within the
 * application.
 */
class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  explicit MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream event_string;
    event_string << "MouseButtonPressedEvent: " << button_;
    return event_string.str();
  }

  EVENT_CLASS_TYPE(kMouseButtonPressed)
};

/**
 * @class MouseButtonReleasedEvent
 * @brief Generated whenever the user releases a mouse button within an
 * application.
 */
class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  explicit MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream event_string;
    event_string << "MouseButtonReleasedEvent: " << button_;
    return event_string.str();
  }

  EVENT_CLASS_TYPE(kMouseButtonReleased)
};

}  // namespace events
}  // namespace engine

#endif  // ENGINE_SRC_CORE_EVENTS_MOUSEEVENT_H_
