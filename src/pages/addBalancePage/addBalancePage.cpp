#include "addBalancePage.h"

#include <emscripten/bind.h>
#include <iostream>
#include <sstream>

#include "../../components/state/State.cpp"
#include "../../router/Router.h"
#include "../../globalState/userState/userState.h"
#include "../../utils/Constants.h"

AddBalancePage *AddBalancePage::instance = nullptr;
State<string> *AddBalancePage::addBalance = new State<string>("0");

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

    myBalance = UserState::getInstance()->getBalanceState();
    addBalance->setState("0");

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

    addBalanceInput->getElement().set("onchange", emscripten::val::module_property("AddBalancePage.addBalanceInputHandler"));
    addButton->getElement().set("onclick", emscripten::val::module_property("AddBalancePage.addBalanceButtonHandler"));
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
    instance = nullptr;
}

void AddBalancePage::addBalanceInputHandler(emscripten::val event)
{
    string value = event["target"]["value"].as<string>();
    addBalance->setState(value);
}

void AddBalancePage::addBalanceButtonHandler(emscripten::val event)
{
    string patchedBalance;
    try {
        string stringUserBalance = UserState::getInstance()->getBalanceState()->getValue();
        string stringAddBalance = addBalance->getValue();
        stringstream ss1(stringUserBalance);
        stringstream ss2(stringAddBalance);
        int userBalance;
        int addBalance;
        ss1 >> userBalance;
        ss2 >> addBalance;
        patchedBalance = to_string(userBalance + addBalance);
    } catch (exception &e)
    {
        std::cout << "error: " << e.what() << std::endl;
        return;
    }
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "PATCH");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = AddBalancePage::addBalanceNetworkHandler;

    string url = Constants::API_URL + "/account/user?uuid=" + UserState::getInstance()->getCurrentUser()->getValue().getUUID(); + "&balance=" + patchedBalance;

    emscripten_fetch(&attr, url.c_str());
}

void  AddBalancePage::addBalanceNetworkHandler(emscripten_fetch_t *fetch)
{
    cout << "addBalanceNetworkHandler" << endl;
    Router::getInstance()->navigate("/main");
}

EMSCRIPTEN_BINDINGS(AddBalancePage)
{
    emscripten::function("AddBalancePage.addBalanceInputHandler", &AddBalancePage::addBalanceInputHandler);
    emscripten::function("AddBalancePage.addBalanceButtonHandler", &AddBalancePage::addBalanceButtonHandler);
}

