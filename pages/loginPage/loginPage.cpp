#include "loginPage.h"
#include "../page/page.h"
#include "../../components/state/State.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

LoginPage::LoginPage(val root): Page(root) {
    webTextState = new State("loading");
    loginText = new State("Login");

    container = new Flex("column", "center", "center", "10px");
    loginButton = new Button(loginText);
    webButton = new Button(webTextState);
    usernameInput = new Input("Username");
    passwordInput = new Input("Password");

    container->appendChildren({usernameInput, passwordInput, loginButton, webButton});
}

void LoginPage::render() {
    root.call<void>("appendChild", container->getElement());
}