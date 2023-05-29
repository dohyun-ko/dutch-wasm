#include "loginPage.h"
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

LoginPage::LoginPage(val root): Page(&root) {
    webTextState = new State<string>("loading");
    loginText = new State<string>("Login");

    container = new Flex("column", "center", "center", "10px");
    loginButton = new Button(loginText);
    webButton = new Button(webTextState);
    usernameInput = new Input("Username");
    passwordInput = new Input("Password");

    container->appendChildren({usernameInput, passwordInput, loginButton, webButton});
}

void LoginPage::render() {
    root->call<void>("appendChild", container->getElement());
}

void LoginPage::remove() {
    root->call<void>("removeChild", container->getElement());
}

LoginPage::~LoginPage() {
    delete webTextState;
    delete loginText;
    delete container;
    delete loginButton;
    delete webButton;
    delete usernameInput;
    delete passwordInput;
}