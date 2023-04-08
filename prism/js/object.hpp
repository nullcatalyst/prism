#pragma once

#include <cstdint>
#include <string>

#include "prism/common/shared.hpp"
#include "prism/wasm/import.hpp"

namespace prism::js {

namespace detail {

// The functions in this namespace aren't intended to be used directly. Instead, use instances of
// the class Object defined below.

// These must match the functions defined in object.ts

using ObjectId = uint32_t;

WASM_IMPORT("object", "createNull") ObjectId object_create_null();
WASM_IMPORT("object", "createBoolean") ObjectId object_create_boolean(bool value);
WASM_IMPORT("object", "createNumber") ObjectId object_create_number(double value);
WASM_IMPORT("object", "createString") ObjectId object_create_string(const char* value);
WASM_IMPORT("object", "createObject") ObjectId object_create_object();
WASM_IMPORT("object", "createArray") ObjectId object_create_array();
WASM_IMPORT("object", "release") ObjectId object_release(ObjectId object_id);

WASM_IMPORT("object", "parse") ObjectId object_parse(const char* json_str);
WASM_IMPORT("object", "stringify") const char* object_stringify(ObjectId object_id);

WASM_IMPORT("object", "isNull") bool object_is_null(const ObjectId object_id);
WASM_IMPORT("object", "isBoolean") bool object_is_boolean(const ObjectId object_id);
WASM_IMPORT("object", "isNumber") bool object_is_number(const ObjectId object_id);
WASM_IMPORT("object", "isString") bool object_is_string(const ObjectId object_id);
WASM_IMPORT("object", "isObject") bool object_is_object(const ObjectId object_id);
WASM_IMPORT("object", "isArray") bool object_is_array(const ObjectId object_id);

WASM_IMPORT("object", "asBoolean") bool object_as_boolean(const ObjectId object_id);
WASM_IMPORT("object", "asNumber") double object_as_number(const ObjectId object_id);
WASM_IMPORT("object", "asString") const char* object_as_string(const ObjectId object_id);

WASM_IMPORT("object", "has")
bool object_has_property(const ObjectId object_id, const char* property);
WASM_IMPORT("object", "get")
ObjectId object_get_property(const ObjectId object_id, const char* property);

WASM_IMPORT("object", "setNullProperty")
void object_set_null_property(const ObjectId object_id, const char* property_name);
WASM_IMPORT("object", "setBooleanProperty")
void object_set_boolean_property(const ObjectId object_id, const char* property_name,
                                 const bool value);
WASM_IMPORT("object", "setNumberProperty")
void object_set_number_property(const ObjectId object_id, const char* property_name,
                                const double value);
WASM_IMPORT("object", "setStringProperty")
void object_set_string_property(const ObjectId object_id, const char* property_name,
                                const char* value);
WASM_IMPORT("object", "setObjectProperty")
void object_set_object_property(const ObjectId object_id, const char* property_name,
                                const ObjectId other_id);

WASM_IMPORT("object", "equalsString")
bool object_equals_string(const ObjectId object_id, const char* str);

WASM_IMPORT("object", "arrayPushObject")
void array_push_object(const ObjectId object_id, const ObjectId other_id);
WASM_IMPORT("object", "arrayPop") void array_pop(const ObjectId object_id);
WASM_IMPORT("object", "arrayLength") uint32_t array_length(const ObjectId object_id);
WASM_IMPORT("object", "arrayAt") ObjectId array_at(const ObjectId object_id, const uint32_t index);

}  // namespace detail

struct object_Object_dtor {
    static void call(const detail::ObjectId object_id) { detail::object_release(object_id); }
};

class Object : public common::Shared<detail::ObjectId, object_Object_dtor> {
    using Parent = common::Shared<detail::ObjectId, object_Object_dtor>;

  public:
    static Object from_raw(const detail::ObjectId obj_id) { return Object{obj_id}; }
    // static Object from_ptr(const void* ptr) {
    //     return Object{static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ptr))};
    // }

    constexpr Object() = default;
    using Parent::Shared;  // Reuse constructors from parent

    [[nodiscard]] detail::ObjectId obj_id() const noexcept {
        return Parent::has() ? Parent::get() : 0;
    }

    [[nodiscard]] static Object null() { return Object::from_raw(detail::object_create_null()); }
    [[nodiscard]] static Object boolean(bool b) {
        return Object::from_raw(detail::object_create_boolean(b));
    }
    [[nodiscard]] static Object number(double num) {
        return Object::from_raw(detail::object_create_number(num));
    }
    [[nodiscard]] static Object string(const char* str) {
        return Object::from_raw(detail::object_create_string(str));
    }
    [[nodiscard]] static Object string(const std::string str) {
        return Object::from_raw(detail::object_create_string(str.c_str()));
    }
    [[nodiscard]] static Object object() {
        return Object::from_raw(detail::object_create_object());
    }
    [[nodiscard]] static Object array() { return Object::from_raw(detail::object_create_array()); }

    [[nodiscard]] static Object parse(const char* json_str) {
        return Object::from_raw(detail::object_parse(json_str));
    }
    [[nodiscard]] static Object parse(const std::string& json_str) {
        return Object::from_raw(detail::object_parse(json_str.c_str()));
    }
    [[nodiscard]] std::string stringify() const {
        return string_from_js(detail::object_stringify(obj_id()));
    }

    [[nodiscard]] bool is_null() const { return detail::object_is_null(obj_id()); }
    [[nodiscard]] bool is_boolean() const { return detail::object_is_boolean(obj_id()); }
    [[nodiscard]] bool is_number() const { return detail::object_is_number(obj_id()); }
    [[nodiscard]] bool is_string() const { return detail::object_is_string(obj_id()); }
    [[nodiscard]] bool is_object() const { return detail::object_is_object(obj_id()); }
    [[nodiscard]] bool is_array() const { return detail::object_is_array(obj_id()); }

    [[nodiscard]] bool has(const char* property) const {
        return detail::object_has_property(obj_id(), property);
    }
    [[nodiscard]] Object get(const char* property) const {
        return Object::from_raw(detail::object_get_property(obj_id(), property));
    }

    bool        as_boolean() const { return detail::object_as_boolean(obj_id()); }
    double      as_number() const { return detail::object_as_number(obj_id()); }
    std::string as_string() const { return string_from_js(detail::object_as_string(obj_id())); }

    void set(const char* property, std::nullptr_t) {
        detail::object_set_null_property(obj_id(), property);
    }
    void set(const char* property, bool b) {
        detail::object_set_boolean_property(obj_id(), property, b);
    }
    void set(const char* property, double num) {
        detail::object_set_number_property(obj_id(), property, num);
    }
    void set(const char* property, const char* str) {
        detail::object_set_string_property(obj_id(), property, str);
    }
    void set(const char* property, const std::string& str) {
        detail::object_set_string_property(obj_id(), property, str.c_str());
    }
    void set(const char* property, const Object& value) {
        detail::object_set_object_property(obj_id(), property, value.obj_id());
    }

    [[nodiscard]] bool operator==(std::nullptr_t) const { return is_null(); }
    // [[nodiscard]] bool operator==(bool b) const;
    // [[nodiscard]] bool operator==(double num) const;
    [[nodiscard]] bool operator==(const char* str) const {
        return detail::object_equals_string(obj_id(), str);
    }
    [[nodiscard]] bool operator==(const std::string& str) const {
        return detail::object_equals_string(obj_id(), str.c_str());
    }
    // [[nodiscard]] bool operator==(const Object& obj) const;

    // Array
    void push(const std::nullptr_t) {
        detail::array_push_object(obj_id(), Object::null().obj_id());
    }
    void push(const bool b) { detail::array_push_object(obj_id(), Object::boolean(b).obj_id()); }
    void push(const double num) {
        detail::array_push_object(obj_id(), Object::number(num).obj_id());
    }
    void push(const char* str) {
        detail::array_push_object(obj_id(), Object::string(str).obj_id());
    }
    void push(const std::string& str) {
        detail::array_push_object(obj_id(), Object::string(str).obj_id());
    }
    void     push(const Object& obj) { detail::array_push_object(obj_id(), obj.obj_id()); }
    void     pop() { detail::array_pop(obj_id()); }
    uint32_t size() const { return detail::array_length(obj_id()); }
    Object   at(const uint32_t index) const {
        return Object::from_raw(detail::array_at(obj_id(), index));
    }

    template <typename T>
    void for_each(T&& callback) const {
        for (uint32_t i = 0, end = size(); i < end; ++i) {
            callback(at(i));
        }
    }

  private:
    static std::string string_from_js(const char* c_str) {
        std::string s{c_str};
        free(const_cast<char*>(c_str));
        return s;
    }
};

}  // namespace prism::js
