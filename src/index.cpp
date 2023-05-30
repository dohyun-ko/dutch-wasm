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

using namespace emscripten;
using json = nlohmann::json;
using namespace std;

val getElementById(string id) {
    return val::global("document").call<val>("getElementById", val(id));
}

int main() {
    val root = getElementById("root");

    LoginPage* loginPage = new LoginPage(root);
    loginPage->render();

    emscripten_sleep(3000);

    loginPage->remove();

    SignUpPage* signUpPage = new SignUpPage(root);
    signUpPage->render();

    auto j3 = json::parse(R"({"username": "test", "password": "test"})");
    cout << j3["username"] << endl;
}