#pragma once

#include <ostream>

#include "status_code.h"

namespace http {

class response {
    friend auto operator<<(std::ostream &out, response const &response) -> std::ostream &;

public:
    response(status_code code) : _code(code) {
    }

    template <status_code Code>
    static auto error() -> response {
        static_assert(Code != status_code::ok);
        return response(Code);
    }

    static auto error() -> response {
        return response(status_code::bad_request);
    }

    static auto ok() -> response {
        return response(status_code::ok);
    }

    auto code() const -> status_code {
        return _code;
    }

private:
    status_code _code;
};

}