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
#include "../../utils/Constants.h"

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

    container = std::make_unique<Element>("div");
    container->getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("grid")
        .setGridTemplateColumns("4fr 3fr");

    leftSide = std::make_unique<Flex>("column", "center", "center", "10px");
    leftSide->getStyle()
        .setWidth("100%")
        .setHeight("100%");

    rightSide = std::make_unique<Flex>("column", "center", "center", "10px");
    rightSide->getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setBackground(Style::primary);

    sendButton = new Button(make_shared<State<string>>("Send"), Style::defaultButtonStyle_shared_ptr());
    receiveButton = new Button(make_shared<State<string>>("Receive"), Style::defaultButtonStyle_shared_ptr());
    makeButton = new Button(make_shared<State<string>>("Make"), Style::defaultButtonStyle_shared_ptr());
    addBalanceButton = new Button(make_shared<State<string>>("Deposit"), Style::defaultButtonStyle_shared_ptr());

    leftSide->appendChildren({sendButton, receiveButton, makeButton, addBalanceButton});

    myBalanceText = std::make_shared<Text>(new State<string>("My Balance"));
    myBalanceText->getStyle()
        .setFontSize("24px")
        .setColor("white");

    balanceText = std::make_shared<Text>(balanceState);
    balanceText->getStyle()
        .setFontSize("24px")
        .setColor(Style::secondary)
        .setBackground(Style::primaryVariant)
        .setBorderRadius("10px")
        .setWidth("150px")
        .setHeight("50px")
        .setTextAlign("center")
        .setLineHeight("50px");

    loginSuccessText = std::make_shared<Text>(loginState);

    loginButton = new Button(new State<string>("Login"), Style::defaultButtonStyle());

    loginButton->getStyle()
        .setBackground(Style::secondary);

    if (userState->getValue().getUUID() == "")
    {
        rightSide->appendChildren({myBalanceText.get(), balanceText.get(), loginButton});
    }
    else
    {
        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);
        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        attr.onsuccess = MainPage::getBalanceNetworkHandler;

        string url = Constants::API_URL + "/account/user?uuid=" + userState->getValue().getUUID();
        emscripten_fetch(&attr, url.c_str());
        rightSide->appendChildren({myBalanceText.get(), balanceText.get(), loginSuccessText.get()});
    }

    container->appendChildren({leftSide.get(), rightSide.get()});

    loginButton->getElement().set("onclick", emscripten::val::module_property("MainPage.loginButtonHandler"));

    if (userState->getValue().getUUID() == "")
    {
        sendButton->getElement().set("onclick", emscripten::val::module_property("MainPage.notLoginedButtonHandler"));
        receiveButton->getElement().set("onclick", emscripten::val::module_property("MainPage.notLoginedButtonHandler"));
        makeButton->getElement().set("onclick", emscripten::val::module_property("MainPage.notLoginedButtonHandler"));
        addBalanceButton->getElement().set("onclick", emscripten::val::module_property("MainPage.notLoginedButtonHandler"));
    }
    else
    {
        sendButton->getElement().set("onclick", emscripten::val::module_property("MainPage.sendButtonHandler"));
        receiveButton->getElement().set("onclick", emscripten::val::module_property("MainPage.receiveButtonHandler"));
        makeButton->getElement().set("onclick", emscripten::val::module_property("MainPage.makeDutchButtonHandler"));
        addBalanceButton->getElement().set("onclick", emscripten::val::module_property("MainPage.addBalanceButtonHandler"));
    }

    MainPage::appendChildren(container.get());
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
    cout << "MainPage::~MainPage()" << endl;
}

void MainPage::sendButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::sendButtonHandler" << std::endl;
    Router::getInstance()->navigate("/send");
}

void MainPage::receiveButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::receiveButtonHandler" << std::endl;
    Router::getInstance()->navigate("/receive");
}

void MainPage::loginButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::loginButtonHandler" << std::endl;
    Router::getInstance()->navigate("/login");
}

void MainPage::makeDutchButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::makeDutchButtonHandler" << std::endl;
    Router::getInstance()->navigate("/makeDutch");
}

void MainPage::addBalanceButtonHandler(emscripten::val event)
{
    std::cout << "MainPage::addBalanceButtonHandler" << std::endl;
    Router::getInstance()->navigate("/addBalance");
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
        MainPage::balanceState->setState("$" + balance);
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
    emscripten::function("MainPage.makeDutchButtonHandler", &MainPage::makeDutchButtonHandler);
    emscripten::function("MainPage.addBalanceButtonHandler", &MainPage::addBalanceButtonHandler);
}