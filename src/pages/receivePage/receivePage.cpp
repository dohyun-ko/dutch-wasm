#include "receivePage.h"
#include "../../components/style/Style.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../globalState/userState/userState.h"

ReceivePage *ReceivePage::instance = nullptr;

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

    dutchItemWrapperStyle = new Style();
    dutchItemWrapperStyle->setWidth("100%")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center")
        .setJustifyContent("space-between")
        .setBackground(Style::secondaryVariant)
        .setBorder("none")
        .setBorderRadius("8px")
        .setAspectRatio("1.618")
        .setPadding("10px 0")
        .setColor(Style::primaryVariant);

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
    dutchItemChargeStyle = new Style();
    dutchItemChargeStyle->setFontSize("16px")
        .setFontWeight("400")
        .setWidth("calc(100\% - 20px)")
        .setTextAlign("right")
        .setPadding("0px 10px 10px 10px")
        .setMargin("0")
        .setHeight("20%");

    dutchItemTitleStyle = new Style();
    dutchItemTitleStyle->setFontSize("16px")
        .setBorder("none")
        .setBorderRadius("8px")
        .setFontSize("20px")
        .setFontWeight("bold")
        .setColor(Style::primaryVariant)
        .setMargin("0");

    string username = UserState::getInstance()->getCurrentUser()->getValue().getUsername();

    dutchItemButtonStyle = new Style();
    dutchItemButtonStyle
        ->setBorder("none")
        .setBorderRadius("6px")
        .setPadding("5px 15px")
        .setMargin("0")
        .setBackground(Style::primaryVariant);

    dutchItemButtonTextState = new State<std::string>("View Detail");

    dutchItem1 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem1");

    dutchItem2 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem2");

    dutchItem3 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem3");

    dutchItem4 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem4");

    dutchItem5 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem5");

    dutchItem6 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem6");

    dutchItemWrapper1 = new Element("div", dutchItemWrapperStyle);
    dutchItemWrapper1->appendChildren({new Text(new State<std::string>("user, user, user"), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(new State<std::string>("$ 50 / 100"), dutchItemChargeStyle),
                                       dutchItem1});

    dutchItemWrapper2 = new Element("div", dutchItemWrapperStyle);
    dutchItemWrapper2->appendChildren({new Text(new State<std::string>("user, user, user"), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(new State<std::string>("$ 50 / 100"), dutchItemChargeStyle),
                                       dutchItem2});

    dutchItemWrapper3 = new Element("div", dutchItemWrapperStyle);
    dutchItemWrapper3->appendChildren({new Text(new State<std::string>("user, user, user"), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(new State<std::string>("$ 50 / 100"), dutchItemChargeStyle),
                                       dutchItem3});

    dutchItemWrapper4 = new Element("div", dutchItemWrapperStyle);
    dutchItemWrapper4->appendChildren({new Text(new State<std::string>("user, user, user"), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(new State<std::string>("$ 50 / 100"), dutchItemChargeStyle),
                                       dutchItem4});

    dutchItemWrapper5 = new Element("div", dutchItemWrapperStyle);
    dutchItemWrapper5->appendChildren({new Text(new State<std::string>("user, user, user"), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(new State<std::string>("$ 50 / 100"), dutchItemChargeStyle),
                                       dutchItem5});

    dutchItemWrapper6 = new Element("div", dutchItemWrapperStyle);
    dutchItemWrapper6->appendChildren({new Text(new State<std::string>("user, user, user"), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(new State<std::string>("$ 50 / 100"), dutchItemChargeStyle),
                                       dutchItem6});

    dutchItemContainer->appendChildren({dutchItemWrapper1,
                                        dutchItemWrapper2,
                                        dutchItemWrapper3,
                                        dutchItemWrapper4,
                                        dutchItemWrapper5,
                                        dutchItemWrapper6});

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
