#include <emscripten/bind.h>
#include <iostream>

#include "signUpPage.h"
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/style/Style.h"

State<string> *SignUpPage::usernameState = new State<string>("");
State<string> *SignUpPage::passwordState = new State<string>("");
State<string> *SignUpPage::emailState = new State<string>("");

SignUpPage::SignUpPage(): Element("div") {
    signUpTextState = new State<string>("Sign Up");
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

    signUpButton->getElement().set("onclick", emscripten::val::module_property("SignUpPage.SignUpButtonHander"));
    usernameInput->getElement().set("onchange", emscripten::val::module_property("SignUpPage.getUsername"));
    passwordInput->getElement().set("onchange", emscripten::val::module_property("SignUpPage.getPassword"));
    emailInput->getElement().set("onchange", emscripten::val::module_property("SignUpPage.getEmail"));

    SignUpPage::appendChildren(container);
}


SignUpPage::~SignUpPage() {
    delete signUpTextState;
    delete container;
    delete signUpButton;
    delete usernameInput;
    delete passwordInput;
    delete emailInput;
}

void SignUpPage::getUsername(emscripten::val e) {
    cout << "SignUpPage.getUsername" << endl;
    string username = e["target"]["value"].as<string>();
    SignUpPage::usernameState->setState(username);
}

void SignUpPage::getPassword(emscripten::val e) {
    cout << "SignUpPage.getPassword" << endl;
    string password = e["target"]["value"].as<string>();
    SignUpPage::passwordState->setState(password);
}

void SignUpPage::getEmail(emscripten::val e) {
    cout << "SignUpPage.getEmail" << endl;
    string email = e["target"]["value"].as<string>();
    SignUpPage::emailState->setState(email);
}

void SignUpPage::SignUpButtonHander(emscripten::val e) {
    string username = SignUpPage::usernameState->getValue();
    string password = SignUpPage::passwordState->getValue();
    string email = SignUpPage::emailState->getValue();

    std::cout << "username: " << username << std::endl;
    std::cout << "password: " << password << std::endl;
    std::cout << "email: " << email << std::endl;
}

EMSCRIPTEN_BINDINGS(SignUpPage)
{
    emscripten::function("SignUpPage.SignUpButtonHander", &SignUpPage::SignUpButtonHander);
    emscripten::function("SignUpPage.getUsername", &SignUpPage::getUsername);
    emscripten::function("SignUpPage.getPassword", &SignUpPage::getPassword);
    emscripten::function("SignUpPage.getEmail", &SignUpPage::getEmail);
}