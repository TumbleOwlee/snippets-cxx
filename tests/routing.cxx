#include "http.h"

#include <iostream>

using namespace http;

class UserController : public Controller {
public:
    auto endpoints() -> Endpoints override {
        return {
            {"/user/add",    BIND_FN(UserController::add)   },
            {"/user/remove", BIND_FN(UserController::remove)},
            {"/user/update", BIND_FN(UserController::update)}
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
            {"/evse/add",    BIND_FN(EvseController::add)   },
            {"/evse/remove", BIND_FN(EvseController::remove)},
            {"/evse/update", BIND_FN(EvseController::update)}
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
            {"/storage/add",    BIND_FN(StorageController::add)   },
            {"/storage/remove", BIND_FN(StorageController::remove)},
            {"/storage/update", BIND_FN(StorageController::update)}
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
