#include "sendDutchPage.h"

#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/style/Style.h"

SendDutchPage *SendDutchPage::instance = nullptr;

SendDutchPage::SendDutchPage() : Element("div")
{
    SendDutchPage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center")
        .setJustifyContent("center");
}

SendDutchPage *SendDutchPage::getInstance()
{
    if (SendDutchPage::instance == nullptr)
    {
        SendDutchPage::instance = new SendDutchPage();
    }

    return SendDutchPage::instance;
}

SendDutchPage::~SendDutchPage()
{
    SendDutchPage::instance = nullptr;
    delete container;
}