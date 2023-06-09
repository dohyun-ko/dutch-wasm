#include "makeDutchPage.h"

MakeDutchPage *MakeDutchPage::instance = nullptr;

MakeDutchPage::MakeDutchPage() : Element("div")
{
    MakeDutchPage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("row")
        .setAlignItems("center")
        .setJustifyContent("center")
        .setGap("10px");

    billContainer = new Flex("column", "center", "center", "10px");
    billContainer->getStyle()
        .setWidth("40%")
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

    charge = new State<string>("0");

    chargeLabel = new Text(new State<string>("Total Charge: "));
    chargeInput = new Input(charge, Style::defaultInputStyle());
    sendUserLabel = new Text(new State<string>("Receiver: "));
    sendUserContainer = new Flex("column", "start", "center", "10px");

    subUserButtonStyle = new Style();
    subUserButtonStyle
        ->setBorder("none")
        .setMargin("0px")
        .setPadding("5px 7px")
        .setBackground("#ff8888")
        .setBorderRadius("5px")
        .setColor(Style::primaryVariant);

    userItemStyle = new Style();
    userItemStyle
        ->setWidth("calc(100% - 20px)")
        .setHeight("30px")
        .setPadding("5px 10px")
        .setBackground(Style::primary)
        .setBorderRadius("5px")
        .setBoxShadow("2px 2px 5px 0px rgba(0,0,0,0.3)")
        .setDisplay("flex")
        .setJustifyContent("space-between")
        .setAlignItems("center");

    userItemNameStyle = new Style();
    userItemNameStyle
        ->setMargin("0px")
        .setPadding("0px")
        .setFontSize("14px");

    sendUserItems[0] = new Element("div", userItemStyle);

    subUserButtons[0] = new Button(new State<string>("X"), subUserButtonStyle);
    sendUserItems[0]->appendChildren({new Text(new State<string>("User1"), userItemNameStyle), subUserButtons[0]}); // to @siwonpada: userName vector<State>로 관리해야하나?

    sendUserContainer->appendChildren({sendUserItems[0]});

    billUpper->appendChildren({chargeLabel, chargeInput, sendUserLabel, sendUserContainer});

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

    dutchType = new State<string>("normal");

    radioContainer = new Flex("row", "center", "center", "10px");
    normalDutchRadio = new Radio(new State<string>("normal"), dutchType, nullptr, "normalDutchRadio");
    raceDutchRadio = new Radio(new State<string>("race"), dutchType, nullptr, "raceDutchRadio");
    relayDutchRadio = new Radio(new State<string>("relay"), dutchType, nullptr, "relayDutchRadio");

    radioContainer->appendChildren({normalDutchRadio, raceDutchRadio, relayDutchRadio});

    makeButton = new Button(new State<string>("Send"), Style::defaultButtonStyle());
    billLower->appendChildren({radioContainer, makeButton});

    billContainer->appendChildren({billTitle, billUpperDivider, billUpper, billLowerDivider, billLower});

    userContainer = new Flex("column", "center", "center", "10px");
    userContainer->getStyle()
        .setWidth("calc(25\% - 20px)")
        .setHeight("calc(50\% - 20px)")
        .setPadding("10px")
        .setBackground(Style::primaryVariant)
        .setBorderRadius("10px");

    addUserButtonStyle = new Style();
    addUserButtonStyle
        ->setBorder("none")
        .setMargin("0px")
        .setPadding("5px 7px")
        .setBackground("#8888ff")
        .setBorderRadius("5px")
        .setColor(Style::primaryVariant);

    userItems[0] = new Element("div", userItemStyle);
    addUserButtons[0] = new Button(new State<string>("+"), addUserButtonStyle);
    userItems[0]->appendChildren({new Text(new State<string>("User1"), userItemNameStyle), addUserButtons[0]});

    userContainer->appendChildren({userItems[0]});

    MakeDutchPage::appendChildren({billContainer, userContainer});
}

MakeDutchPage *MakeDutchPage::getInstance()
{
    if (MakeDutchPage::instance == nullptr)
    {
        MakeDutchPage::instance = new MakeDutchPage();
    }

    return MakeDutchPage::instance;
}

MakeDutchPage::~MakeDutchPage()
{
    delete instance;
}