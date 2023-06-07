#include "mainPage.h"

#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/style/Style.h"

MainPage *MainPage::instance = nullptr;

MainPage::MainPage() : Element("div")
{

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
        .setBackground(Style::primary);

    sendButton = new Button(new State<string>("Send"), Style::defaultButtonStyle());
    receiveButton = new Button(new State<string>("Receive"), Style::defaultButtonStyle());

    leftSide->appendChildren({sendButton, receiveButton});

    myBalanceText = new Text(new State<string>("My Balance"));
    myBalanceText->getStyle()
        .setFontSize("24px")
        .setColor("white");

    balanceText = new Text(myBalance);
    balanceText->getStyle()
        .setFontSize("24px")
        .setColor(Style::secondary)
        .setBackground(Style::primaryVariant)
        .setBorderRadius("10px")
        .setWidth("150px")
        .setHeight("50px")
        .setTextAlign("center")
        .setLineHeight("50px");

    loginButton = new Button(new State<string>("Login"), Style::defaultButtonStyle());

    loginButton->getStyle()
        .setBackground(Style::secondary);

    rightSide->appendChildren({myBalanceText, balanceText, loginButton});

    container->appendChildren({leftSide, rightSide});

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