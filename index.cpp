#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <string>
#include <iostream>

#include "components/button/Button.h"
#include "components/flex/Flex.h"
#include "components/input/Input.h"


using namespace emscripten;
using namespace std;

val getElementById(string id) {
    return val::global("document").call<val>("getElementById", val(id));
}

int main() {
    val root = getElementById("root");

    State* loginText = new State("Login");

    Flex* container = new Flex("column", "center", "center", "10px");
    Button* loginButton = new Button(loginText);
    Input* usernameInput = new Input("Username");
    Input* passwordInput = new Input("Password");

    root.call<void>("appendChild", container->getElement());

    container->appendChildren({usernameInput, passwordInput, loginButton});

    loginButton->setOnClick([&]() {
        loginText->setState("Logout");
    });

}

