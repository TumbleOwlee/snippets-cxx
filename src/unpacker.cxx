#include <iostream>
#include <tuple>
#include <functional>

template<typename... Types>
struct Tuple {
    typedef std::tuple<Types...> Type;
};

template<size_t len, typename C, typename T, typename... Args>
struct Unpacker {
    static inline void call(std::function<C> cb, typename T::Type& t, Args... args) {
        Unpacker<len-1, C, T, std::tuple_element_t<len-1, typename T::Type>, Args...>::call(cb, t, std::get<len-1>(t), args...);
    }
};

template<typename C, typename T, typename... Args>
struct Unpacker<0, C, T, Args...> {
    typedef typename T::Type TupleType;
    static inline void call(std::function<C> cb, TupleType& t, Args... args) {
        cb(args...);
    }
};

template<typename... Args>
static inline void call(std::function<void(Args...)> cb, std::tuple<Args...> t) {
    Unpacker<std::tuple_size_v<std::tuple<Args...>>, void(Args...), Tuple<Args...>>::call(cb, t);
}

int main(int, char**) {
    {    
        std::tuple<> t;
        std::function<void()> fn = []() { std::cout << "No parameters" << std::endl; };
        call(fn, t);
    }
    {    
        std::tuple<int, bool, float> t = {10, true, 33.33};
        std::function<void(int, bool, float)> fn = [](int v1, bool v2, float v3) {
            std::cout << "Parameters: " << v1 << ", " << v2 << ", " << v3 << std::endl; 
        };
        call(fn, t);
    }
    return 0;
}
