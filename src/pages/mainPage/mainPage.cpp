#include "mainPage.h"

#include <iostream>
#include <exception>
#include <emscripten/bind.h>
#include <nlohmann/json.hpp>

#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/style/Style.h"
#include "../../router/Router.h"
#include "../../globalState/userState/userState.h"

using json = nlohmann::json;

MainPage *MainPage::instance = nullptr;

State<User> *MainPage::userState = UserState::getInstance()->getCurrentUser();
State<string> *MainPage::loginState = UserState::getInstance()->getLoginState();
State<string> *MainPage::balanceState = UserState::getInstance()->getBalanceState();

MainPage::MainPage() : Element("div")
{

    MainPage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center")
        .setJustifyContent("center");

    container = new Element("div");
    container->getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("grid")
        .setGridTemplateColumns("4fr 3fr");

    leftSide = new Flex("column", "center", "center", "10px");
    leftSide->getStyle()
        .setWidth("100%")
        .setHeight("100%");

    rightSide = new Flex("column", "center", "center", "10px");
    rightSide->getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setBackground(Style::primary);

    sendButton = new Button(new State<string>("Send"), Style::defaultButtonStyle());
    receiveButton = new Button(new State<string>("Receive"), Style::defaultButtonStyle());

    leftSide->appendChildren({sendButton, receiveButton});

    myBalanceText = new Text(new State<string>("My Balance"));
    myBalanceText->getStyle()
        .setFontSize("24px")
        .setColor("white");

    balanceText = new Text(balanceState);
    balanceText->getStyle()
        .setFontSize("24px")
        .setColor(Style::secondary)
        .setBackground(Style::primaryVariant)
        .setBorderRadius("10px")
        .setWidth("150px")
        .setHeight("50px")
        .setTextAlign("center")
        .setLineHeight("50px");

    loginSuccessText = new Text(loginState);

    loginButton = new Button(new State<string>("Login"), Style::defaultButtonStyle());

    loginButton->getStyle()
        .setBackground(Style::secondary);

    if (userState->getValue().getUUID() == "")
    {
        rightSide->appendChildren({myBalanceText, balanceText, loginButton});
    }
    else
    {
        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);
        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        attr.onsuccess = MainPage::getBalanceNetworkHandler;

        string url = "http://13.124.243.56:8080/account/user?uuid=" + userState->getValue().getUUID();
        emscripten_fetch(&attr, url.c_str());
        rightSide->appendChildren({myBalanceText, balanceText, loginSuccessText});
    }

    container->appendChildren({leftSide, rightSide});

    loginButton->getElement().set("onclick", emscripten::val::module_property("MainPage.loginButtonHandler"));

    if (userState->getValue().getUUID() == "")
    {
        sendButton->getElement().set("onclick", emscripten::val::module_property("MainPage.notLoginedButtonHandler"));
        receiveButton->getElement().set("onclick", emscripten::val::module_property("MainPage.notLoginedButtonHandler"));
    }
    else
    {
        sendButton->getElement().set("onclick", emscripten::val::module_property("MainPage.sendButtonHandler"));
        receiveButton->getElement().set("onclick", emscripten::val::module_property("MainPage.receiveButtonHandler"));
    }

    MainPage::appendChildren(container);
}

MainPage *MainPage::getInstance()
{
    if (MainPage::instance == nullptr)
    {
        MainPage::instance = new MainPage();
    }

    return MainPage::instance;
}

MainPage::~MainPage()
{
    MainPage::instance = nullptr;
    delete container;
}

void MainPage::sendButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::sendButtonHandler" << std::endl;
    Router *router = Router::getInstance();
    router->navigate("/send");
}

void MainPage::receiveButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::receiveButtonHandler" << std::endl;
    Router *router = Router::getInstance();
    router->navigate("/receive");
}

void MainPage::loginButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::loginButtonHandler" << std::endl;
    Router *router = Router::getInstance();
    router->navigate("/login");
}

void MainPage::makeDutchButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::makeDutchButtonHandler" << std::endl;
    Router *router = Router::getInstance();
    router->navigate("/makeDutch");
}

void MainPage::notLoginedButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::notLoginedButtonHandler" << std::endl;
    emscripten_run_script("alert('Need Login')");
}

void MainPage::getBalanceNetworkHandler(emscripten_fetch_t *fetch)
{
    std::cout << "MainPage::getBalanceNetworkHandler" << std::endl;
    std::cout << "fetch->status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        string balance = j["balance"];
        MainPage::balanceState->setState("$"+balance);
    }
    catch (json::parse_error &e)
    {
        std::cout << "json::parse_error: " << e.what() << std::endl;
    }
    catch (exception &e)
    {
        cout << "network error" << endl;
    }

    emscripten_fetch_close(fetch);
}

EMSCRIPTEN_BINDINGS(MainPage)
{
    emscripten::function("MainPage.loginButtonHandler", &MainPage::loginButtonHandler);
    emscripten::function("MainPage.sendButtonHandler", &MainPage::sendButtonHandler);
    emscripten::function("MainPage.receiveButtonHandler", &MainPage::receiveButtonHandler);
    emscripten::function("MainPage.notLoginedButtonHandler", &MainPage::notLoginedButtonHandler);
}