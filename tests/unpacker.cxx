#include "unpacker.hxx"
#include <iostream>
#include <tuple>

int main(int, char **) {
    {
        std::tuple<> t;
        snippets::call<void>([]() { std::cout << "No parameters" << std::endl; }, t);
    }
    {
        std::tuple<int> t = {10};
        snippets::call<void>([](int v1) { std::cout << v1 << std::endl; }, t);
    }
    {
        std::tuple<int, bool> t = {0, true};
        snippets::call<void>([](int v1, bool v2) { std::cout << v1 << ", " << v2 << std::endl; }, t);
    }
    {
        std::tuple<int, bool, float> t = {0, true, 33.33};
        snippets::call<void>(
            [](int v1, bool v2, float v3) { std::cout << v1 << ", " << v2 << ", " << v3 << std::endl; }, t);
    }
    {
        std::tuple<int, bool, float> t = {0, true, 33.33};
        std::cerr << snippets::call<bool>(
            [](int v1, bool v2, float v3) -> bool {
                std::cout << v1 << ", " << v2 << ", " << v3 << std::endl;
                return false;
            },
            t);
    }
    return 0;
}
