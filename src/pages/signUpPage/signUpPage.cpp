#include "signUpPage.h"
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/style/Style.h"

SignUpPage::SignUpPage(val root): Page(&root) {
    signUpTextState = new State<string>("Login");
    backwardTextState = new State<string>("Back");

    header = new Flex("row", "center", "center", "10px");
    container = new Flex("column", "center", "center", "10px");
    usernameInput = new Input("Username");
    passwordInput = new Input("Password");
    emailInput = new Input("Email");
    backwardButton = new Button(backwardTextState);
    signUpButton = new Button(signUpTextState);

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
    container->appendChildren({header, usernameInput, passwordInput, emailInput, signUpButton});
}

void SignUpPage::render() {
    root->call<void>("appendChild", container->getElement());
}

void SignUpPage::remove() {
    root->call<void>("removeChild", container->getElement());
}

SignUpPage::~SignUpPage() {
    delete signUpTextState;
    delete container;
    delete signUpButton;
    delete usernameInput;
    delete passwordInput;
    delete emailInput;
}