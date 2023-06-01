#include "signUpPage.h"
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/style/Style.h"

SignUpPage* SignUpPage::instance = nullptr;

SignUpPage::SignUpPage(): Element("div") {
    signUpTextState = new State<string>("Login");
    backwardTextState = new State<string>("Back");

    container = new Flex("column", "center", "center", "10px");
    usernameInput = new Input(new State<string>("Username"));
    passwordInput = new Input(new State<string>("Password"));
    emailInput = new Input(new State<string>("Email"));
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

    usernameInput->getStyle()
        .setWidth("148px")
        .setHeight("44px")
        .setBorder("1px solid black")
        .setBorderRadius("6px")
        .setPadding("0 25px");

    passwordInput->getStyle()
        .setWidth("148px")
        .setHeight("44px")
        .setBorder("1px solid black")
        .setBorderRadius("6px")
        .setPadding("0 25px");

    emailInput->getStyle()
        .setWidth("148px")
        .setHeight("44px")
        .setBorder("1px solid black")
        .setBorderRadius("6px")
        .setPadding("0 25px");

    container->appendChildren({usernameInput, passwordInput, emailInput, signUpButton});

    SignUpPage::appendChildren(container);
}

SignUpPage* SignUpPage::getInstance() {
    if (SignUpPage::instance == nullptr) {
        SignUpPage::instance = new SignUpPage();
    }

    return SignUpPage::instance;
}

SignUpPage::~SignUpPage() {
    SignUpPage::instance = nullptr;
    delete signUpTextState;
    delete container;
    delete signUpButton;
    delete usernameInput;
    delete passwordInput;
    delete emailInput;
}