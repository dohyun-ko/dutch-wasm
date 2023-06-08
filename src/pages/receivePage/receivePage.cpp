#include "receivePage.h"
#include "../../components/style/Style.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../globalState/userState/userState.h"
#include "../../globalState/receiveDutchState/receiveDutchState.h"

ReceivePageStates::ReceivePageStates()
{
    sendUserList = new State<string>("");
    targetAmount = new State<string>("");
}

State<string>* ReceivePageStates::getSendUserList()
{
    return sendUserList;
}

State<string>* ReceivePageStates::getTargetAmount()
{
    return targetAmount;
}

ReceivePage *ReceivePage::instance = nullptr;
ReceivePageStates* ReceivePage::dutchList[6] = {new ReceivePageStates(), new ReceivePageStates(), new ReceivePageStates(), new ReceivePageStates(), new ReceivePageStates(), new ReceivePageStates()};
State<vector<string>> *ReceivePage::dutchUUIDList = ReceiveDutchState::getInstance()->getReceiveUUIDs();


ReceivePage::ReceivePage() : Element("div")
{
    ReceivePage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("row")
        .setAlignItems("center")
        .setJustifyContent("center");
    prevButton = new Button(new State<string>("⬅"));
    nextButton = new Button(new State<string>("➡"));

    dutchItemContainer = new Element("div");
    dutchItemContainer->getStyle()
        .setWidth("70%")
        .setHeight("50%")
        .setDisplay("grid")
        .setGridTemplateColumns("repeat(3, 1fr)")
        .setGap("25px");

    dutchItemStyle = new Style();
    dutchItemStyle->setWidth("100%")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center")
        .setJustifyContent("space-between")
        .setBackground(Style::secondaryVariant)
        .setBorder("none")
        .setBorderRadius("8px")
        .setFontSize("20px")
        .setFontWeight("bold")
        .setColor(Style::secondaryVariant)
        .setAspectRatio("1.618")
        .setPadding("10px 0")
        .setColor("white");

    dutchItemUserNameStyle = new Style();
    dutchItemUserNameStyle->setFontSize("12px")
        .setFontWeight("600")
        .setWidth("calc(100\% - 20px)")
        .setTextAlign("left")
        .setBackground(Style::primary)
        .setPadding("10px 10px 0px 10px")
        .setMargin("0")
        .setHeight("20%");

    dutchItemChargeStyle = new Style();
    dutchItemChargeStyle->setFontSize("16px")
        .setFontWeight("400")
        .setWidth("calc(100\% - 20px)")
        .setTextAlign("right")
        .setPadding("0px 10px 10px 10px")
        .setMargin("0")
        .setHeight("20%");
    
    string username = UserState::getInstance()->getCurrentUser()->getValue().getUsername();

    dutchItem1 = new Button(new State<string>("Dutch to "+username), dutchItemStyle);
    dutchItem1->appendChildren({new Text(new State<string>("User Name, User Name"), dutchItemUserNameStyle),
                                new Text(new State<string>("$ 50 / 100"), dutchItemChargeStyle)});

    dutchItem2 = new Button(new State<string>("Dutch to "+username), dutchItemStyle);
    dutchItem2->appendChildren({new Text(new State<string>("User Name, User Name"), dutchItemUserNameStyle),
                                new Text(new State<string>("$ 50 / 100"), dutchItemChargeStyle)});

    dutchItem3 = new Button(new State<string>("Dutch to "+username), dutchItemStyle);
    dutchItem3->appendChildren({new Text(new State<string>("User Name, User Name"), dutchItemUserNameStyle),
                                new Text(new State<string>("$ 50 / 100"), dutchItemChargeStyle)});

    dutchItem4 = new Button(new State<string>("Dutch to "+username), dutchItemStyle);
    dutchItem4->appendChildren({new Text(new State<string>("User Name, User Name"), dutchItemUserNameStyle),
                                new Text(new State<string>("$ 50 / 100"), dutchItemChargeStyle)});

    dutchItem5 = new Button(new State<string>("Dutch to "+username), dutchItemStyle);
    dutchItem5->appendChildren({new Text(new State<string>("User Name, User Name"), dutchItemUserNameStyle),
                                new Text(new State<string>("$ 50 / 100"), dutchItemChargeStyle)});

    dutchItem6 = new Button(new State<string>("Dutch to "+username), dutchItemStyle);
    dutchItem6->appendChildren({new Text(new State<string>("User Name, User Name"), dutchItemUserNameStyle),
                                new Text(new State<string>("$ 50 / 100"), dutchItemChargeStyle)});

    dutchItemContainer->appendChildren({dutchItem1, dutchItem2, dutchItem3, dutchItem4, dutchItem5, dutchItem6});

    ReceivePage::appendChildren({prevButton, dutchItemContainer, nextButton});
}

ReceivePage *ReceivePage::getInstance()
{
    if (ReceivePage::instance == nullptr)
    {
        ReceivePage::instance = new ReceivePage();
    }

    return ReceivePage::instance;
}

ReceivePage::~ReceivePage()
{
    ReceivePage::instance = nullptr;

    delete dutchItemContainer;
}
