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
#include "pages/mainPage/mainPage.h"

using namespace emscripten;
using json = nlohmann::json;

val getElementById(std::string id) {
    return val::global("document").call<val>("getElementById", val(id));
}

int main() {
    val root = getElementById("root");

    Element* layout = new Element("div");

    root.call<void>("appendChild", layout->getElement());

    Router router(
        layout,
        {
            {"/login", new LoginPage()},
            {"/signUp", new SignUpPage()},
            {"/main", new MainPage()}
        },
        "/signUp"
    );

    while (true) {
        emscripten_sleep(100);
    }

    // emscripten_set_main_loop() // TODO: use this instead of sleep


    // router.navigate("/signUp");

    // SignUpPage* signUpPage = new SignUpPage(root);
    // signUpPage->render();

    // emscripten_sleep(3000);

    // signUpPage->remove();

    // mainPage->render();
}