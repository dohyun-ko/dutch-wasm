#include "mainPage.h"

MainPage::MainPage(val root): Page(&root) {
    backwardTextState = new State<string>("Back");
    logoutTextState = new State<string>("Logout");
    addMoneyTextState = new State<string>("Add money");
    sendTextState = new State<string>("Send");

    container = new Flex("column", "center", "center", "10px");
    header = new Flex("row", "center", "center", "10px");
    body = new Flex("column", "center", "center", "10px");
    moneyContainer = new Flex("row", "center", "center", "10px");

    backwardButton = new Button(backwardTextState);
    logoutButton = new Button(logoutTextState);
    addMoneyButton = new Button(addMoneyTextState);
    sendButton = new Button(sendTextState);

    header->appendChildren({backwardButton, logoutButton});
    moneyContainer->appendChildren({addMoneyButton});
    body->appendChildren({sendButton});
    container->appendChildren({header, moneyContainer, body});
}

void MainPage::render() {
    root->call<void>("appendChild", container->getElement());
}

void MainPage::update() {}

void MainPage::remove() {
    root->call<void>("removeChild", container->getElement());
}

MainPage::~MainPage() {
    delete backwardTextState;
    delete logoutTextState;
    delete addMoneyTextState;
    delete sendTextState;

    delete container;
    delete header;
    delete body;
    delete moneyContainer;

    delete backwardButton;
    delete logoutButton;
    delete addMoneyButton;
    delete sendButton;
}