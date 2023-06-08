#include "sendDetailPage.h"

SendDetailPage *SendDetailPage::instance = nullptr;
State<string> *SendDetailPage::nowUUID = SendDutchState::getInstance()->getNowUUID();
State<string> *SendDetailPage::charge = new State<string>("0");
State<string> *SendDetailPage::sendCharge = new State<string>("0");

SendDetailPage::SendDetailPage() : Element("div")
{
    myBalance = UserState::getInstance()->getBalanceState();

    SendDetailPage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center")
        .setJustifyContent("center");

    billContainer = new Flex("column", "center", "center", "10px");
    billContainer->getStyle()
        .setWidth("50%")
        .setHeight("50%")
        .setBackground(Style::primaryVariant)
        .setBorderRadius("10px");

    billTitle = new Text(new State<string>("Dutch Detail"));
    billTitle->getStyle()
        .setFontSize("24px")
        .setFontWeight("bold");

    billUpper = new Element("div");
    billUpper->getStyle()
        .setMargin("10px")
        .setDisplay("grid")
        .setGridTemplateColumns("100px 1fr")
        .setGap("10px");

    chargeLabel = new Text(new State<string>("Total Charge: "));
    chargeText = new Text(charge);
    receiveUserLabel = new Text(new State<string>("Receiver: "));
    receiveUserText = new Text(new State<string>("User Name"));
    myBalanceLabel = new Text(new State<string>("My Balance: "));
    myBalanceText = new Text(myBalance);
    sendChargeLabel = new Text(new State<string>("Send Charge: "));
    sendChargeText = new Text(sendCharge);
    sendChargeInput = new Input(new State<string>("amount to send"), Style::defaultInputStyle()); // 조건부 렌더링

    billUpper->appendChildren({chargeLabel, chargeText, receiveUserLabel, receiveUserText, myBalanceLabel, myBalanceText, sendChargeLabel, sendChargeInput});

    billUpperDivider = new Element("div");
    billUpperDivider->getStyle()
        .setWidth("100%")
        .setHeight("0px")
        .setBorder("1px dotted black");
    billLowerDivider = new Element("div");
    billLowerDivider->getStyle()
        .setWidth("100%")
        .setHeight("0px")
        .setBorder("1px dotted black");

    billLower = new Flex("column", "center", "center", "10px");
    billLower->getStyle()
        .setMargin("10px");

    sendButton = new Button(new State<string>("Send"), Style::defaultButtonStyle());

    billLower->appendChildren({sendButton});

    billContainer->appendChildren({billTitle, billUpperDivider, billUpper, billLowerDivider, billLower});

    SendDetailPage::appendChildren({billContainer});
}

SendDetailPage *SendDetailPage::getInstance()
{
    if (SendDetailPage::instance == nullptr)
    {
        SendDetailPage::instance = new SendDetailPage();
    }

    return SendDetailPage::instance;
}

SendDetailPage::~SendDetailPage()
{
    SendDetailPage::instance = nullptr;

    delete billContainer;
}

void SendDetailPage::sendButtonHandler(emscripten::val event)
{
    std::cout << "SendDetailPage.sendButtonHandler" << std::endl;
}

void SendDetailPage::inputHandler(emscripten::val event)
{
    std::cout << "SendDetailPage.inputHandler" << std::endl;
    sendCharge->setState(event["target"]["value"].as<string>());
}