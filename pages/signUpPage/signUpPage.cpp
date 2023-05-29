#include "signUpPage.h"
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

SignUpPage::SignUpPage(val root): Page(&root) {
    webTextState = new State<string>("loading");
    loginText = new State<string>("Login");

    container = new Flex("column", "center", "center", "10px");
    loginButton = new Button(loginText);
    webButton = new Button(webTextState);
    usernameInput = new Input("Username");
    passwordInput = new Input("Password");
    nicknameInput = new Input("Nickname");

    container->appendChildren({usernameInput, passwordInput, nicknameInput, loginButton, webButton});
}

void SignUpPage::render() {
    root->call<void>("appendChild", container->getElement());
}

void SignUpPage::remove() {
    root->call<void>("removeChild", container->getElement());
}

SignUpPage::~SignUpPage() {
    delete webTextState;
    delete loginText;
    delete container;
    delete loginButton;
    delete webButton;
    delete usernameInput;
    delete passwordInput;
    delete nicknameInput;
}