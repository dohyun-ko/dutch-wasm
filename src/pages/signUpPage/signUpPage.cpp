#include <emscripten/bind.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>

#include "signUpPage.h"
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/style/Style.h"
#include "../../apiClient/apiClient.h"

using json = nlohmann::json;
using namespace std;

State<string> *SignUpPage::usernameState = new State<string>("");
State<string> *SignUpPage::passwordState = new State<string>("");
State<string> *SignUpPage::emailState = new State<string>("");

SignUpPage* SignUpPage::instance = nullptr;

SignUpPage::SignUpPage(): Element("div") {
    signUpTextState = new State<string>("Sign Up");

    container = new Flex("column", "center", "center", "10px");
    usernameInput = new Input(new State<string>("Username"), Style::defaultInputStyle());
    passwordInput = new Input(new State<string>("Password"), Style::defaultInputStyle());
    emailInput = new Input(new State<string>("Email"), Style::defaultInputStyle());
    signUpButton = new Button(signUpTextState, Style::defaultButtonStyle());

    container->appendChildren({usernameInput, passwordInput, emailInput, signUpButton});

    signUpButton->getElement().set("onclick", emscripten::val::module_property("SignUpPage.SignUpButtonHander"));
    usernameInput->getElement().set("onchange", emscripten::val::module_property("SignUpPage.getUsername"));
    passwordInput->getElement().set("onchange", emscripten::val::module_property("SignUpPage.getPassword"));
    emailInput->getElement().set("onchange", emscripten::val::module_property("SignUpPage.getEmail"));

    passwordInput->getElement().set("type", "password");

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

    if(username == "" || password == "" || email == "") {
        std::cout << "username, password, email is empty" << std::endl;
        return;
    }

    ApiClient apiClient = ApiClient("http://15.165.55.135:8080/user", "POST", {
        QueryParam("username", username),
        QueryParam("password", password),
        QueryParam("email", email)
    }, "", 5000);

    try {
        apiClient.send();
        json data = apiClient.getJsonData();
        std::cout << data["uuid"] << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

EMSCRIPTEN_BINDINGS(SignUpPage)
{
    emscripten::function("SignUpPage.SignUpButtonHander", &SignUpPage::SignUpButtonHander);
    emscripten::function("SignUpPage.getUsername", &SignUpPage::getUsername);
    emscripten::function("SignUpPage.getPassword", &SignUpPage::getPassword);
    emscripten::function("SignUpPage.getEmail", &SignUpPage::getEmail);
}