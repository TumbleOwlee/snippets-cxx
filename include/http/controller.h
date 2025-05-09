#pragma once

#include <functional>
#include <initializer_list>
#include <map>

#include "request.h"
#include "response.h"

namespace http {

using request_handler = std::function<auto(request const &)->response>;

class endpoint : public std::pair<std::string_view, request_handler> {
public:
    endpoint(std::string_view const path, request_handler const handler) 
    : std::pair<std::string_view, request_handler>(path, handler) {
    }
};

#define ENDPOINT(PATH, FUNCTION) endpoint(PATH, std::bind(&FUNCTION, this, std::placeholders::_1))

class endpoints : public std::map<std::string_view, request_handler> {
public:
    endpoints() = default;
    endpoints(std::initializer_list<std::pair<std::string_view const, request_handler>> const list) {
        for (auto& v : list) {
            insert(v);
        }
    }

private:
    std::map<std::string_view, request_handler> handlers;
};

class controller {
public:
    virtual ~controller() = default;
    virtual auto endpoints() -> endpoints = 0;
};

}