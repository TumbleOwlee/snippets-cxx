#pragma once

#include <string>

namespace http {

class request {
public:
    request(std::string const &path) : _path(path) {
    }

    auto path() const -> std::string const & {
        return _path;
    }

private:
    std::string const _path;
};

}