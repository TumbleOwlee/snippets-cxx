#include "http.h"

#include <iostream>

using namespace http;

class UserController : public Controller {
public:
    auto endpoints() -> Endpoints override {
        return {
            ENDPOINT("/user/add", UserController::add),
            ENDPOINT("/user/remove", UserController::remove),
            ENDPOINT("/user/update", UserController::update)
        };
    }

    auto add(Request const &request) -> Response {
        return Response::Ok();
    }

    auto remove(Request const &request) -> Response {
        return Response::Err();
    }

    auto update(Request const &request) -> Response {
        return Response::Err<StatusCode::NotFound>();
    }
};

class EvseController : public Controller {
public:
    auto endpoints() -> Endpoints override {
        return {
            ENDPOINT("/evse/add", EvseController::add),
            ENDPOINT("/evse/remove", EvseController::remove),
            ENDPOINT("/evse/update", EvseController::update)
        };
    }

    auto add(Request const &request) -> Response {
        return Response::Ok();
    }

    auto remove(Request const &request) -> Response {
        return Response::Err();
    }

    auto update(Request const &request) -> Response {
        return Response::Err<StatusCode::NotFound>();
    }
};

class StorageController : public Controller {
public:
    auto endpoints() -> Endpoints override {
        return {
            ENDPOINT("/storage/add", StorageController::add),
            ENDPOINT("/storage/remove", StorageController::remove),
            ENDPOINT("/storage/update", StorageController::update)
        };
    }

    auto add(Request const &request) -> Response {
        return Response::Ok();
    }

    auto remove(Request const &request) -> Response {
        return Response::Err();
    }

    auto update(Request const &request) -> Response {
        return Response::Err<StatusCode::NotFound>();
    }
};

int main(int argc, char **argv) {
    Router router;
    router.attach<UserController>();
    router.attach<EvseController>();
    router.attach<StorageController>();

    Request addUser("/user/add");
    std::cerr << static_cast<int>(router.handle(addUser).code()) << std::endl;

    Request removeUser("/user/remove");
    std::cerr << static_cast<int>(router.handle(removeUser).code()) << std::endl;

    Request updateUser("/user/update");
    std::cerr << static_cast<int>(router.handle(updateUser).code()) << std::endl;

    return 0;
}
