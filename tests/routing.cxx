#include <iostream>

#include "http/controller.h"
#include "http/response.h"
#include "http/request.h"
#include "http/router.h"
#include "http/status_code.h"

using namespace http;

class user_controller : public controller {
public:
    auto endpoints() -> class endpoints override {
        return {
            ENDPOINT("/user/add", user_controller::add),
            ENDPOINT("/user/remove", user_controller::remove),
            ENDPOINT("/user/update", user_controller::update)
        };
    }

    auto add(request const &request) -> response {
        return response::ok();
    }

    auto remove(request const &request) -> response {
        return response::error();
    }

    auto update(request const &request) -> response {
        return response::error<status_code::not_found>();
    }
};

int main(int argc, char **argv) {
    router router;
    router.attach<user_controller>();

    request addUser("/user/add");
    std::cerr << static_cast<int>(router.handle(addUser).code()) << std::endl;

    request removeUser("/user/remove");
    std::cerr << static_cast<int>(router.handle(removeUser).code()) << std::endl;

    request updateUser("/user/update");
    std::cerr << static_cast<int>(router.handle(updateUser).code()) << std::endl;

    return 0;
}
