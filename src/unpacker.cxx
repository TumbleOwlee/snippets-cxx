#include <iostream>
#include <tuple>
#include <functional>

template<typename... Types>
struct Tuple {
    typedef std::tuple<Types...> Type;
    typedef std::tuple_size<Type> Size;
};

template<size_t len, typename C, typename T, typename... Args>
struct Unpacker {
    static inline void call(std::function<C> cb, typename T::Type& t, Args&... args) {
        typedef typename std::tuple_element<len-1, typename T::Type>::type Tail;
        Unpacker<len-1, C, T, Tail, Args...>::call(cb, t, std::get<len-1>(t),  args...);
    }
};

template<typename C, typename T, typename... Args>
struct Unpacker<0, C, T, Args...> {
    static inline void call(std::function<C> cb, typename T::Type& t, Args&... args) {
        cb(args...);
    }
};

template<typename F, typename... Args>
static inline void call(F cb, std::tuple<Args...> t) {
    std::function<void(Args...)> fn = cb;
    Unpacker<typename Tuple<Args...>::Size{}, void(Args...), Tuple<Args...>>::call(fn, t);
}

int main(int, char**) {
    {    
        std::tuple<> t;
        call([]() { std::cout << "No parameters" << std::endl; }, t);
    }
    {    
        std::tuple<int> t = {10};
        call([](int v1) { std::cout << v1 << std::endl; }, t);
    }
    {    
        std::tuple<int, bool> t = {0, true};
        call([](int v1, bool v2) { std::cout << v1 << ", " << v2 << std::endl; }, t);
    }
    {    
        std::tuple<int, bool, float> t = {0, true, 33.33};
        call([](int v1, bool v2, float v3) { std::cout << v1 << ", " << v2 << ", " << v3 << std::endl; }, t);
    }
    return 0;
}
