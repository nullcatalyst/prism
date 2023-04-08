#pragma once

#include <cstdint>

#include "prism/common/debug.hpp"

namespace prism::common {

template <typename T>
class DefaultDtor {
  public:
    static void call(T& value) {
        // Do nothing and allow the value's destructor to be called, allowing it to be destroyed
        // normally.
    }
};

/**
 * This is a smart pointer that is used to wrap shared values.
 *
 * It is a reference counted pointer that will automatically drop the value when the last reference
 * is released.
 *
 * A std::shared_ptr could have been used, but it has some overhead that we don't need. For example,
 * the reference count is stored in a separate block of memory, which means that the pointer to the
 * value is not contiguous with the reference count and needing more than a single pointer value per
 * reference.
 *
 * Note that this does NOT have any support for weak references. So be careful not to create a cycle
 * of shared references, or you WILL have a memory leak.
 *
 * `Dtor` must be a class that has a static `Dtor::call(T&)` class function, that will be called
 * when the value is released.
 */
template <typename T, typename Dtor = DefaultDtor<T>>
    requires requires(T& value) { Dtor::call(value); }
class Shared {
    struct Impl {
        T        value;
        uint32_t ref_count;
    };

    Impl* _impl = nullptr;

  public:
    constexpr Shared() : _impl{nullptr} {}
    constexpr Shared(const Shared& other) : _impl{other._impl} { retain(); }
    constexpr Shared(Shared&& other) : _impl{other._impl} { other._impl = nullptr; }
    ~Shared() { release(); }

    template <typename... Args>
    explicit Shared(Args&&... args)
        : _impl{new Impl{
              .value     = T{std::forward<Args>(args)...},
              .ref_count = 1,
          }} {}

    Shared& operator=(const Shared& other) {
        release();
        _impl = other._impl;
        retain();
        return *this;
    }

    Shared& operator=(Shared&& other) {
        release();
        _impl       = other._impl;
        other._impl = nullptr;
        return *this;
    }

    constexpr T& operator*() const { return _impl->value; }
    constexpr T* operator->() const { return &_impl->value; }

    /// !!! ONLY USE THIS IF YOU ARE ABSOLUTELY SURE !!!
    void UNSAFE_release_without_dtor() {
        PRISM_DEBUG_ASSERT_CONDITION(_impl == nullptr || _impl->ref_count == 1);

        delete _impl;
        _impl = nullptr;
    }

  protected:
    // These are simply additional member functions that can be used in the case that another class
    // derives from this one. They are not used by the base class itself.

    [[nodiscard]] constexpr bool has() const { return _impl != nullptr; }
    [[nodiscard]] constexpr T&   get() const { return _impl->value; }

    void replace_value(const T& new_value) {
        // This is the only copy, reuse the stored Impl to avoid a deallocation and allocation
        if (_impl != nullptr && _impl->ref_count == 1) {
            Dtor::call(_impl->value);
            _impl->value = new_value;
            return;
        }

        release();
        _impl = new Impl{new_value, 1};
    }

    void retain() {
        if (_impl == nullptr) [[unlikely]] {
            return;
        }
        ++_impl->ref_count;
    }

    void release() {
        if (_impl == nullptr) [[unlikely]] {
            return;
        }

        --_impl->ref_count;
        if (_impl->ref_count == 0) {
            Dtor::call(_impl->value);
            delete _impl;
        }

        _impl = nullptr;
    }
};

template <typename T, typename Dtor>
    requires requires(T* value) { Dtor::call(value); }
class Shared<T*, Dtor> {
    T*        _value;
    uint32_t* _ref_count;

  public:
    constexpr Shared() : _value{nullptr}, _ref_count{0} {}
    constexpr Shared(const std::nullptr_t) : _value{nullptr}, _ref_count{0} {}
    constexpr Shared(T* value) : _value{value}, _ref_count{nullptr} {
        if (_value != nullptr) {
            _ref_count = new uint32_t{1};
        }
    }
    constexpr Shared(const Shared& other) : _value{other._value}, _ref_count{other._ref_count} {
        retain();
    }
    constexpr Shared(Shared&& other) : _value{other._value}, _ref_count{other._ref_count} {
        other._value     = nullptr;
        other._ref_count = nullptr;
    }
    ~Shared() { release(); }

    Shared& operator=(const std::nullptr_t) {
        release();
        return *this;
    }

    Shared& operator=(const Shared& other) {
        release();
        _value     = other._value;
        _ref_count = other._ref_count;
        retain();
        return *this;
    }

    Shared& operator=(Shared&& other) {
        release();
        _value           = other._value;
        _ref_count       = other._ref_count;
        other._value     = nullptr;
        other._ref_count = nullptr;
        return *this;
    }

    constexpr          operator T*() const { return _value; }
    constexpr const T& operator*() const { return *_value; }
    constexpr T*       operator->() const { return _value; }

    /// !!! ONLY USE THIS IF YOU ARE ABSOLUTELY SURE !!!
    void UNSAFE_release_without_dtor() {
        PRISM_DEBUG_ASSERT_CONDITION(_ref_count == nullptr || *_ref_count == 1);

        delete _ref_count;
        _value     = nullptr;
        _ref_count = nullptr;
    }

  protected:
    // These are simply additional member functions that can be used in the case that another class
    // derives from this one. They are not used by the base class itself.

    [[nodiscard]] constexpr bool has() const { return _value != nullptr; }
    [[nodiscard]] constexpr T*   get() const { return _value; }

    void replace_value(T* new_value) {
        // This is the only copy, reuse the stored ref_count to avoid both a deallocation and
        // an allocation.
        if (_ref_count != nullptr && *_ref_count == 1) {
            Dtor::call(_value);
            _value = new_value;
            return;
        }

        release();

        _value     = new_value;
        _ref_count = new uint32_t{1};
    }

    void retain() {
        if (_ref_count == nullptr) [[unlikely]] {
            return;
        }
        ++(*_ref_count);
    }

    void release() {
        if (_ref_count == nullptr) [[unlikely]] {
            return;
        }

        --(*_ref_count);
        if (*_ref_count == 0) {
            Dtor::call(_value);
            delete _ref_count;
        }

        _value     = nullptr;
        _ref_count = nullptr;
    }
};

}  // namespace prism::common
