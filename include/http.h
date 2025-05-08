#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#define ENDPOINT(PATH, FUNCTION) { PATH, std::bind(&FUNCTION, this, std::placeholders::_1) }

namespace http {

enum class StatusCode {
    Ok = 200,
    BadRequest = 400,
    NotFound = 404,
};

class Request {
public:
    Request(std::string const &path) : _path(path) {
    }

    auto path() const -> std::string const & {
        return _path;
    }

private:
    std::string const _path;
};

class Response {
    friend auto operator<<(std::ostream &out, Response const &response) -> std::ostream &;

public:
    Response(StatusCode code) : _code(code) {
    }

    template <StatusCode Code>
    static auto Err() -> Response {
        static_assert(Code != StatusCode::Ok);
        return Response(Code);
    }

    static auto Err() -> Response {
        return Response(StatusCode::BadRequest);
    }

    static auto Ok() -> Response {
        return Response(StatusCode::Ok);
    }

    auto code() const -> StatusCode {
        return _code;
    }

private:
    StatusCode _code;
};

using RequestHandler = std::function<auto(Request const &)->Response>;
using Endpoints = std::map<std::string_view, RequestHandler>;

class Controller {
public:
    virtual ~Controller() = default;
    virtual auto endpoints() -> Endpoints = 0;
};

class Router {
public:
    template <typename T>
    auto attach() -> void {
        std::unique_ptr<Controller> ctrl(new T());
        for (auto &e : ctrl->endpoints()) {
            if (endpoints.contains(e.first)) {
                abort();
            }
            endpoints.insert(e);
        }
        controllers.emplace_back(std::move(ctrl));
    }

    auto handle(Request const &request) -> Response {
        auto iter = endpoints.find(request.path());
        if (iter != endpoints.end()) {
            return iter->second(request);
        }
        return Response(StatusCode::NotFound);
    }

private:
    Endpoints endpoints;
    std::vector<std::unique_ptr<Controller>> controllers;
};

} // namespace http
