#include "mainPage.h"

#include <iostream>

#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/style/Style.h"
#include "../../router/Router.h"

MainPage* MainPage::instance = nullptr;

MainPage::MainPage(): Element("div") {

    MainPage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center")
        .setJustifyContent("center");

    myBalance = new State<string>("0.00");

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
        .setBackground(Style::primaryBlue);

    sendButton = new Button(new State<string>("Send"), Style::defaultButtonStyle());
    receiveButton = new Button(new State<string>("Receive"), Style::defaultButtonStyle());

    leftSide->appendChildren({sendButton, receiveButton});

    myBalanceText = new Text(new State<string>("My Balance"));
    myBalanceText->getStyle()
        .setFontSize("24px")
        .setColor("white");

    balanceText = new Text(myBalance);

    rightSide->appendChildren({myBalanceText,balanceText});

    container->appendChildren({leftSide, rightSide});

    MainPage::appendChildren(container);
}

MainPage* MainPage::getInstance() {
    if (MainPage::instance == nullptr) {
        MainPage::instance = new MainPage();
    }

    return MainPage::instance;
}

MainPage::~MainPage() {
    MainPage::instance = nullptr;
    delete container;
}

void MainPage::sendButtonHandler(emscripten::val event) {
    std::cout << "MainPage::sendButtonHandler" << std::endl;
    Router* router = Router::getInstance();
    router->navigate("/send");
}

void MainPage::receiveButtonHandler(emscripten::val event) {
    std::cout << "MainPage::receiveButtonHandler" << std::endl;
    Router* router = Router::getInstance();
    router->navigate("/receive");
}

void MainPage::loginButtonHandler(emscripten::val event) {
    std::cout << "MainPage::loginButtonHandler" << std::endl;
    Router* router = Router::getInstance();
    router->navigate("/login");
}

void MainPage::makeDutchButtonHandler(emscripten::val event) {
    std::cout << "MainPage::makeDutchButtonHandler" << std::endl;
    Router* router = Router::getInstance();
    router->navigate("/makeDutch");
}