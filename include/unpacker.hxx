#pragma once

#include <functional>
#include <tuple>

namespace snippets {

/**
 * Tuple struct
 *
 * \details This struct provides the static type and size of a tuple.
 * \param TYPES Types of the tuple elements
 */
template <typename... TYPES>
struct Tuple {
    typedef std::tuple<TYPES...> Type;
    typedef std::tuple_size<Type> Size;
};

/**
 * Unpacker class
 *
 * \details This class provides a way to unpack a tuple and call a function with its elements.
 *
 * \param OUTPUT Output type
 * \param LENGTH Number of elements in the tuple
 * \param FUNCTION Function type
 * \param TUPLE Tuple type
 * \param ARGS Remaining arguments
 */
template <typename OUTPUT, size_t LENGTH, typename FUNCTION, typename TUPLE, typename... ARGS>
struct Unpacker {
    /**
     * Call function with tuple elements
     *
     * \details This function calls the function with the tuple elements.
     *
     * \param FUNCTION Function to call
     * \param TUPLE Tuple
     * \param ARGS Remaining arguments
     * \return void
     */
    static inline auto call(std::function<FUNCTION> cb, typename TUPLE::Type &t, ARGS &...args) -> OUTPUT {
        typedef typename std::tuple_element<LENGTH - 1, typename TUPLE::Type>::type Tail;
        return Unpacker<OUTPUT, LENGTH - 1, FUNCTION, TUPLE, Tail, ARGS...>::call(cb, t, std::get<LENGTH - 1>(t),
                                                                                  args...);
    }
};

/**
 * Unpacker class specialization
 *
 * \details This class provides a way to unpack a tuple and call a function with its elements.
 *
 * \param OUTPUT Output type
 * \param FUNCTION Function type
 * \param TUPLE Tuple type
 * \param ARGS Remaining arguments
 */
template <typename OUTPUT, typename FUNCTION, typename TUPLE, typename... ARGS>
struct Unpacker<OUTPUT, 0, FUNCTION, TUPLE, ARGS...> {
    /**
     * Call function with tuple elements
     *
     * \details This function calls the function with the tuple elements.
     *
     * \param OUTPUT Output type
     * \param FUNCTION Function to call
     * \param TUPLE Tuple
     * \param ARGS Remaining arguments
     * \return OUTPUT
     */
    static inline auto call(std::function<FUNCTION> cb, typename TUPLE::Type &t, ARGS &...args) -> OUTPUT {
        return cb(args...);
    }
};

/**
 * Call function with tuple elements
 *
 * \details This function calls the function with the tuple elements.
 *
 * \param OUTPUT Output type
 * \param FUNCTION Function to call
 * \param TUPLE Tuple type
 * \return OUTPUT
 */
template <typename OUTPUT, typename FUNCTION, typename... ARGS>
static inline auto call(FUNCTION cb, std::tuple<ARGS...> t) -> OUTPUT {
    std::function<auto(ARGS...)->OUTPUT> fn = cb;
    return Unpacker<OUTPUT, typename Tuple<ARGS...>::Size{}, OUTPUT(ARGS...), Tuple<ARGS...>>::call(fn, t);
}

} // namespace snippets
