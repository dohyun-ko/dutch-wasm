#include "receiveDetailPage.h"
#include "../../components/style/Style.h"

ReceiveDetailPage *ReceiveDetailPage::instance = nullptr;

ReceiveDetailPage::ReceiveDetailPage() : Element("div")
{
    charge = new State<string>("0");

    ReceiveDetailPage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center")
        .setJustifyContent("center");

    billContainer = std::make_unique<Flex>("column", "center", "center", "10px");
    billContainer->getStyle()
        .setWidth("50%")
        .setHeight("50%")
        .setBackground(Style::primaryVariant)
        .setBorderRadius("10px");

    billTitle = std::make_unique<Text>(new State<string>("Dutch Detail"));
    billTitle->getStyle()
        .setFontSize("24px")
        .setFontWeight("bold");

    billUpper = std::make_unique<Element>("div");
    billUpper->getStyle()
        .setMargin("10px")
        .setDisplay("grid")
        .setGridTemplateColumns("100px 1fr")
        .setGap("10px");

    chargeLabel = std::make_unique<Text>(new State<string>("Charge Received: "));
    chargeText = new Text(charge);

    billUpper->appendChildren({chargeLabel.get(), chargeText});

    billUpperDivider = std::make_unique<Element>("div");
    billUpperDivider->getStyle()
        .setWidth("100%")
        .setHeight("0px")
        .setBorder("1px dotted black");
    billLowerDivider = std::make_unique<Element>("div");
    billLowerDivider->getStyle()
        .setWidth("100%")
        .setHeight("0px")
        .setBorder("1px dotted black");

    billLower = std::make_unique<Flex>("column", "center", "center", "10px");
    billLower->getStyle()
        .setMargin("10px");

    completeButton = new Button(make_shared<State<string>>("Send"), Style::defaultButtonStyle_shared_ptr());

    billLower->appendChildren({completeButton});

    billContainer->appendChildren({billTitle.get(), billUpperDivider.get(), billUpper.get(), billLowerDivider.get(), billLower.get()});

    ReceiveDetailPage::appendChildren({billContainer.get()});
}

ReceiveDetailPage *ReceiveDetailPage::getInstance()
{
    if (ReceiveDetailPage::instance == nullptr)
    {
        ReceiveDetailPage::instance = new ReceiveDetailPage();
    }

    return ReceiveDetailPage::instance;
}

ReceiveDetailPage::~ReceiveDetailPage()
{
    delete instance;
}