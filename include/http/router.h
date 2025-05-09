#pragma once

#include <memory>

#include "controller.h"

namespace http {

class router {
public:
    router() = default;

    template <typename T>
    auto attach() -> void {
        std::unique_ptr<controller> ctrl(new T());
        for (auto &e : ctrl->endpoints()) {
            if (_endpoints.contains(e.first)) {
                abort();
            }
            _endpoints.insert(e);
        }
        _controllers.emplace_back(std::move(ctrl));
    }

    auto handle(request const &request) -> response {
        auto iter = _endpoints.find(request.path());
        if (iter != _endpoints.end()) {
            return iter->second(request);
        }
        return response(status_code::not_found);
    }

private:
    using controllers = std::vector<std::unique_ptr<controller>>;
    endpoints _endpoints;
    controllers _controllers;
};

}