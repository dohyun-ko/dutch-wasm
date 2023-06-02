#include "loginPage.h"
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/style/Style.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/style/Style.h"
#include "../../apiClient/apiClient.h"
#include "../../router/Router.h"
#include "../../components/element/Element.h"
#include <iostream>
#include <functional>
#include <emscripten/bind.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

State<string> *LoginPage::loginTextState = new State<string>("Login");
LoginPage* LoginPage::instance = nullptr;

LoginPage::LoginPage(): Element("div") {
    signUpTextState = new State<string>("Sign Up");
    backwardTextState = new State<string>("Back");

    buttonStyle = new Style();

    container = new Flex("column", "center", "center", "10px");
    loginButton = new Button(loginTextState, Style::defaultButtonStyle());
    signUpButton = new Button(signUpTextState, Style::defaultButtonStyle());
    usernameInput = new Input(new State<string>("Username"), Style::defaultInputStyle());
    passwordInput = new Input(new State<string>("Password"), Style::defaultInputStyle());

    container->appendChildren({usernameInput, passwordInput, loginButton, signUpButton});

    loginButton->getElement().set("onclick", emscripten::val::module_property("LoginPage.LoginButtonHander"));
    signUpButton->getElement().set("onclick", emscripten::val::module_property("LoginPage.SignUpButtonHander"));

    LoginPage::appendChildren(container);
}

LoginPage* LoginPage::getInstance() {
    if (LoginPage::instance == nullptr) {
        LoginPage::instance = new LoginPage();
    }

    return LoginPage::instance;

}

void LoginPage::LoginButtonHander(emscripten::val e)
{
    std::cout << "LoginPage::LoginButtonHander()" << std::endl;
    return;
}

void LoginPage::SignUpButtonHander(emscripten::val e) {
    std::cout << "LoginPage::SignUpButtonHander()" << std::endl;
    Router* router = Router::getInstance();
    std::cout << "router: " << router << std::endl;
    router->navigate("/signUp"); // TODO: maybe it's better to change navigate to a static method
    std::cout << "router->navigate" << std::endl;
}

LoginPage::~LoginPage() {
    LoginPage::instance = nullptr;
    delete loginTextState;
    delete signUpTextState;
    delete container;
    delete loginButton;
    delete signUpButton;
    delete usernameInput;
    delete passwordInput;
}

EMSCRIPTEN_BINDINGS(Page)
{
    emscripten::function("LoginPage.LoginButtonHander", &LoginPage::LoginButtonHander);
    emscripten::function("LoginPage.SignUpButtonHander", &LoginPage::SignUpButtonHander);
}
