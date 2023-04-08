#pragma once

#include <cstdint>

#include "prism/js/object.hpp"
#include "prism/wasm/import.hpp"

namespace prism::js {

namespace detail {

// The functions in this namespace aren't intended to be used directly. Instead, use instances of
// the classes HtmlElement and HtmlCanvasElement defined below.

WASM_IMPORT("dom", "getById")
uint32_t dom_get_by_id(const char* id);

WASM_IMPORT("dom", "onMouseMoved")
uint32_t dom_on_mouse_moved(uint32_t element_obj,
                            void (*callback)(double x, double y, void* user_data), void* user_data);

WASM_IMPORT("dom", "onMouseButtonDown")
uint32_t dom_on_mouse_button_down(uint32_t element_obj,
                                  void (*callback)(uint32_t button, void* user_data),
                                  void* user_data);

WASM_IMPORT("dom", "onMouseButtonUp")
uint32_t dom_on_mouse_button_up(uint32_t element_obj,
                                void (*callback)(uint32_t button, void* user_data),
                                void* user_data);

WASM_IMPORT("dom", "onKeyDown")
uint32_t dom_on_key_down(uint32_t element_obj, void (*callback)(uint32_t key_code, void* user_data),
                         void*    user_data);

WASM_IMPORT("dom", "onKeyUp")
uint32_t dom_on_key_up(uint32_t element_obj, void (*callback)(uint32_t key_code, void* user_data),
                       void*    user_data);

}  // namespace detail

class HtmlElement : public Object {
  public:
    using Object::Object;

    static HtmlElement from_raw(const uint32_t obj_id) { return HtmlElement{obj_id}; }
    static HtmlElement get_by_id(const char* id) {
        return HtmlElement::from_raw(detail::dom_get_by_id(id));
    }

    void on_mouse_moved(void (*callback)(double x, double y, void* user_data), void* user_data) {
        detail::dom_on_mouse_moved(obj_id(), callback, user_data);
    }

    void on_mouse_button_down(void (*callback)(uint32_t button, void* user_data), void* user_data) {
        detail::dom_on_mouse_button_down(obj_id(), callback, user_data);
    }

    void on_mouse_button_up(void (*callback)(uint32_t button, void* user_data), void* user_data) {
        detail::dom_on_mouse_button_up(obj_id(), callback, user_data);
    }

    void on_key_down(void (*callback)(uint32_t key_code, void* user_data), void* user_data) {
        detail::dom_on_key_down(obj_id(), callback, user_data);
    }

    void on_key_up(void (*callback)(uint32_t key_code, void* user_data), void* user_data) {
        detail::dom_on_key_up(obj_id(), callback, user_data);
    }
};

class HtmlCanvasElement : public HtmlElement {
  public:
    using HtmlElement::HtmlElement;

    static HtmlCanvasElement from_raw(const uint32_t obj_id) { return HtmlCanvasElement{obj_id}; }
    static HtmlCanvasElement get_by_id(const char* id) {
        return HtmlCanvasElement::from_raw(detail::dom_get_by_id(id));
    }

    uint32_t width() const { return static_cast<uint32_t>(get("width").as_number()); }
    uint32_t height() const { return static_cast<uint32_t>(get("height").as_number()); }
};

}  // namespace prism::js
