#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <emscripten/fetch.h>
#include <string>
#include <iostream>

#include "components/button/Button.h"
#include "components/flex/Flex.h"
#include "components/input/Input.h"
#include "request/request.h"
#include "components/state/State.cpp"
#include "components/style/Style.h"

using namespace emscripten;
using namespace std;

val getElementById(string id) {
    return val::global("document").call<val>("getElementById", val(id));
}

int main() {
    val root = getElementById("root");

    State<string>* loginText = new State<string>("Login");

    Flex* container = new Flex("column", "center", "center", "10px");
    Button* loginButton = new Button(loginText);
    Input* usernameInput = new Input("Username");
    Input* passwordInput = new Input("Password");

    root.call<void>("appendChild", container->getElement());


    loginButton->getStyle()
        .setWidth("200px")
        .setHeight("44px")
        .setBackground("#405cf5")
        .setBorder("none")
        .setBorderRadius("6px")
        .setFontSize("1rem")
        .setColor("#FFFFFF")
        .setPadding("0 25px");

    container->appendChildren({usernameInput, passwordInput, loginButton});

    loginButton->setOnClick([&]() {
        loginText->setState("Logout");
    });
    
    Request* request = new Request("http://localhost:3000", "GET");
    request->setOnSuccess([](emscripten_fetch_t *fetch) {
        cout << "Success" << endl;
        cout << fetch->status << endl;
        cout << fetch->data << endl;
    });
    request->setOnError([](emscripten_fetch_t *fetch) {
        cout << "Error" << endl;
    });
    request->send();
    cout << loginButton->getStyle().getCssString() << endl;
}