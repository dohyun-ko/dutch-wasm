#include "addBalancePage.h"
#include "../../components/state/State.cpp"

AddBalancePage *AddBalancePage::instance = nullptr;

AddBalancePage::AddBalancePage() : Element("div")
{
    AddBalancePage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setJustifyContent("center")
        .setAlignItems("center");

    container = new Flex("column", "center", "center");
    balanceGrid = new Element("div");
    balanceGrid->getStyle()
        .setDisplay("grid")
        .setGridTemplateColumns("150px 1fr")
        .setGap("10px");

    myBalance = new State<string>("0");
    addBalance = new State<string>("0");

    Style *textStyle = new Style();
    textStyle->setFontSize("16px")
        .setFontWeight("bold")
        .setTextAlign("center")
        .setColor(Style::primaryVariant);

    myBalanceText = new Text(myBalance, textStyle);
    addBalanceInput = new Input(new State<string>("amount to add"), Style::defaultInputStyle());

    myBalanceLabel = new Text(new State<std::string>("My Balance:"), textStyle);
    addBalanceLabel = new Text(new State<std::string>("Add Balance:"), textStyle);

    balanceGrid->appendChildren({myBalanceLabel, myBalanceText, addBalanceLabel, addBalanceInput});

    addButton = new Button(new State<std::string>("Add"), Style::defaultButtonStyle());
    addButton->getStyle()
        .setMargin("20px 0 0 0");

    container->appendChildren({balanceGrid, addButton});
    AddBalancePage::appendChildren(container);
}

AddBalancePage *AddBalancePage::getInstance()
{
    if (AddBalancePage::instance == nullptr)
    {
        AddBalancePage::instance = new AddBalancePage();
    }

    return AddBalancePage::instance;
}

AddBalancePage::~AddBalancePage()
{
    delete instance;
}