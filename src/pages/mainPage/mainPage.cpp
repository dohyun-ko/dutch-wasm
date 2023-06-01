#include "mainPage.h"


MainPage* MainPage::instance = nullptr;

MainPage::MainPage(): Element("div") {
    logoutTextState = new State<string>("Logout");
    addMoneyTextState = new State<string>("Add money");
    sendTextState = new State<string>("Send");

    container = new Flex("column", "center", "center", "10px");
    body = new Flex("column", "center", "center", "10px");
    moneyContainer = new Flex("row", "center", "center", "10px");

    logoutButton = new Button(logoutTextState);
    addMoneyButton = new Button(addMoneyTextState);
    sendButton = new Button(sendTextState);

    moneyContainer->appendChildren({addMoneyButton});
    body->appendChildren({sendButton});
    container->appendChildren({moneyContainer, body});

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
    delete backwardTextState;
    delete logoutTextState;
    delete addMoneyTextState;
    delete sendTextState;

    delete container;
    delete body;
    delete moneyContainer;

    delete backwardButton;
    delete logoutButton;
    delete addMoneyButton;
    delete sendButton;
}