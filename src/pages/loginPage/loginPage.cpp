#include "loginPage.h"
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/style/Style.h"

LoginPage::LoginPage(val root): Page(&root) {
    loginTextState = new State<string>("Login");
    signUpTextState = new State<string>("Sign Up");
    backwardTextState = new State<string>("Back");

    header = new Flex("row", "center", "center", "10px");
    container = new Flex("column", "center", "center", "10px");
    backwardButton = new Button(backwardTextState);
    loginButton = new Button(loginTextState);
    signUpButton = new Button(signUpTextState);
    usernameInput = new Input("Username");
    passwordInput = new Input("Password");

    backwardButton->getStyle()
        .setWidth("20px")
        .setHeight("20px")
        .setBackground("none")
        .setBorder("none")
        .setFontSize("1rem")
        .setColor("#000000")
        .setPadding("0 25px");

    loginButton->getStyle()
        .setWidth("200px")
        .setHeight("44px")
        .setBackground("#405cf5")
        .setBorder("none")
        .setBorderRadius("6px")
        .setFontSize("1rem")
        .setColor("#FFFFFF")
        .setPadding("0 25px");

    signUpButton->getStyle()
        .setWidth("200px")
        .setHeight("44px")
        .setBackground("#405cf5")
        .setBorder("none")
        .setBorderRadius("6px")
        .setFontSize("1rem")
        .setColor("#FFFFFF")
        .setPadding("0 25px");

    header->appendChildren({backwardButton});
    container->appendChildren({header, usernameInput, passwordInput, loginButton, signUpButton});
}

void LoginPage::render() {
    root->call<void>("appendChild", container->getElement());
}

void LoginPage::remove() {
    root->call<void>("removeChild", container->getElement());
}

LoginPage::~LoginPage() {
    delete loginTextState;
    delete signUpTextState;
    delete container;
    delete loginButton;
    delete signUpButton;
    delete usernameInput;
    delete passwordInput;
}