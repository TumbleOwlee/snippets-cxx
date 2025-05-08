#pragma once

#include <type_traits>

namespace snippets {

/*!
 * \brief A class that provides a snapshot of a value
 */
template <typename T>
class snapshot {
    static_assert(!std::is_pointer<T>::value);

public:
    /*!
     * \brief Constructor
     *
     * This constructor initializes the internal value and snapshot value using the types constructor by passing
     * through the arguments.
     *
     * \param args The arguments to initialize the value
     */
    template <typename... ARGS>
    snapshot(ARGS... args) : _value(args...), _snapshot(args...) {
    }

    /*!
     * \brief Get the current value
     *
     * This function returns a reference to the current value of the object.
     * It can be used to modify the value directly.
     *
     * \return A reference to the current value
     */
    auto operator->() -> T & {
        return _value;
    }

    /*!
     * \brief Save the current value as a snapshot
     *
     * This function saves the current value of the object as a snapshot.
     * The snapshot can be retrieved later using the get() function.
     */
    auto save() -> void {
        _snapshot = _value;
    }

    /*!
     * \brief Get the last snapshot of the value
     *
     * \return The last snapshot of the value as const reference
     */
    auto get() -> T const & {
        return _snapshot;
    }

private:
    // The mutable value
    T _value;
    // The last snapshot of the value
    T _snapshot;
};

} // namespace snippets
