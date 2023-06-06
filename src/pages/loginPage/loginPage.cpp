#include "loginPage.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/style/Style.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/style/Style.h"
#include "../../components/text/Text.h"
#include "../../router/Router.h"
#include "../../components/element/Element.h"
#include <iostream>
#include <functional>
#include <emscripten/bind.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

LoginPage *LoginPage::instance = nullptr;

State<string> *LoginPage::usernameState = new State<string>("");
State<string> *LoginPage::passwordState = new State<string>("");
State<string> *LoginPage::loginSuccessState = new State<string>("test");

LoginPage::LoginPage() : Element("div")
{
    loginTextState = new State<string>("Login");
    signUpTextState = new State<string>("Sign Up");

    buttonStyle = new Style();

    container = new Flex("column", "center", "center", "10px");
    loginButton = new Button(loginTextState, Style::defaultButtonStyle());
    signUpButton = new Button(signUpTextState, Style::defaultButtonStyle());
    usernameInput = new Input(new State<string>("Username"));
    passwordInput = new Input(new State<string>("Password"));
    loginText = new Text(loginSuccessState);

    passwordInput->getElement().set("type", "password");

    container->appendChildren({usernameInput, passwordInput, loginButton, signUpButton, loginText});

    usernameInput->getElement().set("onchange", emscripten::val::module_property("LoginPage.getUsername"));
    passwordInput->getElement().set("onchange", emscripten::val::module_property("LoginPage.getPassword"));
    loginButton->getElement().set("onclick", emscripten::val::module_property("LoginPage.LoginButtonHandler"));
    signUpButton->getElement().set("onclick", emscripten::val::module_property("LoginPage.SignUpButtonHandler"));

    LoginPage::appendChildren(container);
}

LoginPage::~LoginPage()
{
    LoginPage::instance = nullptr;
    delete loginTextState;
    delete signUpTextState;
    delete container;
    delete loginButton;
    delete signUpButton;
    delete usernameInput;
    delete passwordInput;
}

LoginPage *LoginPage::getInstance()
{
    if (LoginPage::instance == nullptr)
    {
        LoginPage::instance = new LoginPage();
    }

    return LoginPage::instance;
}

void LoginPage::LoginButtonHandler(emscripten::val e)
{
    std::cout << "LoginPage::LoginButtonHander()" << std::endl;
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = LoginPage::LoginSuccessHandler;
    attr.onerror = LoginPage::LoginfailedHandler;
    loginSuccessState->setState("loading...");

    string url = "http://15.165.55.135:8080/user/login?username=" + LoginPage::usernameState->getValue() + "&password=" + LoginPage::passwordState->getValue();
    emscripten_fetch(&attr, url.c_str());

    return;
}

void LoginPage::LoginSuccessHandler(emscripten_fetch_t *fetch)
{
    cout << "LoginPage::LoginNetworkHandler()" << endl;
    cout << "fetch->status: " << fetch->status << endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        LoginPage::loginSuccessState->setState(j["uuid"]);
    }
    catch (json::parse_error &e)
    {
        cout << "parse error: " << e.what() << endl;
    }

    emscripten_fetch_close(fetch);
}

void LoginPage::LoginfailedHandler(emscripten_fetch_t *fetch)
{
    cout << "LoginPage::LoginfailedHandler()" << endl;
    cout << "fetch->status: " << fetch->status << endl;
    if (fetch->status == 401)
    {
        LoginPage::loginSuccessState->setState("login failed");
    }
    emscripten_fetch_close(fetch);
}

void LoginPage::SignUpButtonHandler(emscripten::val e)
{
    std::cout << "LoginPage::SignUpButtonHander()" << std::endl;
    Router *router = Router::getInstance();
    std::cout << "router: " << router << std::endl;
    router->navigate("/signUp"); // TODO: maybe it's better to change navigate to a static method
    std::cout << "router->navigate" << std::endl;
}

void LoginPage::getUsername(emscripten::val e)
{
    cout << "LoginPage::getUsername()" << endl;
    string username = e["target"]["value"].as<string>();
    LoginPage::usernameState->setState(username);
}

void LoginPage::getPassword(emscripten::val e)
{
    cout << "LoginPage::getPassword()" << endl;
    string password = e["target"]["value"].as<string>();
    LoginPage::passwordState->setState(password);
}

EMSCRIPTEN_BINDINGS(LoginPage)
{
    emscripten::function("LoginPage.LoginButtonHandler", &LoginPage::LoginButtonHandler);
    emscripten::function("LoginPage.SignUpButtonHandler", &LoginPage::SignUpButtonHandler);
    emscripten::function("LoginPage.getUsername", &LoginPage::getUsername);
    emscripten::function("LoginPage.getPassword", &LoginPage::getPassword);
}
