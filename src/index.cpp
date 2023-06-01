#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <emscripten/fetch.h>
#include <string>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

#include "components/button/Button.h"
#include "components/flex/Flex.h"
#include "components/input/Input.h"
#include "components/state/State.cpp"
#include "components/style/Style.h"
#include "apiClient/apiClient.h"
#include "pages/loginPage/loginPage.h"
#include "pages/signUpPage/signUpPage.h"
#include "router/Router.h"

using namespace emscripten;
using json = nlohmann::json;

val getElementById(std::string id) {
    return val::global("document").call<val>("getElementById", val(id));
}

int main() {
    val root = getElementById("root");

    Router router(
        {
            {"/login", new LoginPage(root)},
            {"/signUp", new SignUpPage(root)}
        },
        "/login"
    );

    emscripten_sleep(3000);

    router.navigate("/signUp");

    return 0;
}