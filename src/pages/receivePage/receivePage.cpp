#include "receivePage.h"

#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>

#include "../../components/style/Style.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../globalState/userState/userState.h"
#include "../../globalState/receiveDutchState/receiveDutchState.h"

using json = nlohmann::json;

ReceivePageStates::ReceivePageStates()
{
    sendUserList = new State<string>("");
    targetAmount = new State<string>("");
    dutchUUID = "";
}

ReceivePageStates::~ReceivePageStates()
{
    delete sendUserList;
    delete targetAmount;
}

State<string> *ReceivePageStates::getSendUserList()
{
    return sendUserList;
}

State<string> *ReceivePageStates::getTargetAmount()
{
    return targetAmount;
}

string ReceivePageStates::getDutchUUID()
{
    return dutchUUID;
}

void ReceivePageStates::setDutchUUID(string uuid)
{
    dutchUUID = uuid;
}

ReceivePage *ReceivePage::instance = nullptr;
ReceivePageStates *ReceivePage::dutchList[6] = {new ReceivePageStates(), new ReceivePageStates(), new ReceivePageStates(), new ReceivePageStates(), new ReceivePageStates(), new ReceivePageStates()};
State<vector<string>> *ReceivePage::dutchUUIDList = ReceiveDutchState::getInstance()->getReceiveUUIDs();


ReceivePage::ReceivePage() : Element("div")
{
    currentPageNumber = 0;

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

    nextButton->getElement().set("onclick", emscripten::val::module_property("ReceivePage.nextButtonHandler"));
    prevButton->getElement().set("onclick", emscripten::val::module_property("ReceivePage.prevButtonHandler"));
    dutchItem1->getElement().set("onclick", emscripten::val::module_property("ReceivePage.receiveDutchButtonHandler"));
    dutchItem2->getElement().set("onclick", emscripten::val::module_property("ReceivePage.receiveDutchButtonHandler"));
    dutchItem3->getElement().set("onclick", emscripten::val::module_property("ReceivePage.receiveDutchButtonHandler"));
    dutchItem4->getElement().set("onclick", emscripten::val::module_property("ReceivePage.receiveDutchButtonHandler"));
    dutchItem5->getElement().set("onclick", emscripten::val::module_property("ReceivePage.receiveDutchButtonHandler"));
    dutchItem6->getElement().set("onclick", emscripten::val::module_property("ReceivePage.receiveDutchButtonHandler"));

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = ReceivePage::getDutchListHandler;

    string url = "http://13.124.243.56:8080/dutch/normal/user?user_uuid=" + UserState::getInstance()->getCurrentUser()->getValue().getUUID();
    emscripten_fetch(&attr, url.c_str());
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

void ReceivePage::receiveDutchButtonHandler(emscripten::val event)
{
    std::cout << "ReceivePage::receiveDutchButtonHandler" << std::endl;
    string buttonId = event["target"]["id"].as<std::string>();
    buttonId.erase(buttonId.begin(), buttonId.begin() + 9);
    std::stringstream ssInt(buttonId);
    int index = 0;
    ssInt >> index;
    index--;

    ReceiveDutchState::getInstance()->getNowUUID()->setState(dutchList[index]->getDutchUUID());

    Router::getInstance()->navigate("/receiveDetail");
}

void ReceivePage::nextButtonHandler(emscripten::val event)
{
    std::cout << "ReceivePage::nextButtonHandler" << std::endl;
    if (currentPageNumber * 6 + 6 >= dutchUUIDList->getValue().size())
    {
        return;
    }
    currentPageNumber++;

    for (size_t i = 0; i < 6; i++)
    {
        if (dutchUUIDList->getValue().size() <= currentPageNumber * 6 + i)
        {
            dutchList[i]->getSendUserList()->setState("");
            dutchList[i]->getTargetAmount()->setState("");
            continue;
        }
        std::cout << "ReceiveDutchList: " << dutchUUIDList->getValue()[currentPageNumber * 6 + i] << std::endl;
        dutchList[i]->setDutchUUID(dutchUUIDList->getValue()[currentPageNumber * 6 + i]);

        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);
        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        attr.onsuccess = ReceivePage::getDutchInfoHandler;

        string url = "http://13.124.243.56:8080/dutch/normal?dutch_uuid=" + dutchUUIDList->getValue()[currentPageNumber * 6 + i];
        emscripten_fetch(&attr, url.c_str());
    }
}

void ReceivePage::prevButtonHandler(emscripten::val event)
{
    std::cout << "ReceivePage::prevButtonHandler" << std::endl;
    if (currentPageNumber == 0)
    {
        return;
    }
    currentPageNumber--;

    for (size_t i = 0; i < 6; i++)
    {
        if (dutchUUIDList->getValue().size() <= currentPageNumber * 6 + i)
        {
            dutchList[i]->getSendUserList()->setState("");
            dutchList[i]->getTargetAmount()->setState("");
            continue;
        }
        std::cout << "ReceiveDutchList: " << dutchUUIDList->getValue()[currentPageNumber * 6 + i] << std::endl;
        dutchList[i]->setDutchUUID(dutchUUIDList->getValue()[currentPageNumber * 6 + i]);

        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);
        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        attr.onsuccess = ReceivePage::getDutchInfoHandler;

        string url = "http://13.124.243.56:8080/dutch/normal?dutch_uuid=" + dutchUUIDList->getValue()[i + currentPageNumber * 6];
        emscripten_fetch(&attr, url.c_str());
    }
}

void ReceivePage::getDutchListHandler(emscripten_fetch_t *fetch)
{
    std::cout << "ReceivePage::getDutchLIstHandler" << std::endl;
    std::cout << "status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        dutchUUIDList->setState(j["dutch_"]); // 이거 고쳐야함
        for (size_t i = 0; i < (dutchUUIDList->getValue().size() < 6 ? dutchUUIDList->getValue().size() : 6); i++)
        {
            std::cout << "ReceiveDutchList: " << dutchUUIDList->getValue()[i] << std::endl;
            dutchList[i]->setDutchUUID(dutchUUIDList->getValue()[i]);

            emscripten_fetch_attr_t attr;
            emscripten_fetch_attr_init(&attr);
            strcpy(attr.requestMethod, "GET");
            attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
            attr.onsuccess = ReceivePage::getDutchInfoHandler;

            string url = "http://13.124.243.56:8080/dutch/normal?dutch_uuid=" + dutchUUIDList->getValue()[i];
            emscripten_fetch(&attr, url.c_str());
        }
    }
    catch (json::parse_error &e)
    {
        cout << "ReceivePage::getDutchListHandler: parse error" << e.what() << endl;
    }
    emscripten_fetch_close(fetch);
}

void ReceivePage::getDutchInfoHandler(emscripten_fetch_t *fetch)
{
    std::cout << "ReceivePage::getDutchInfoHandler" << std::endl;
    std::cout << "status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));

        int index;
        for (size_t i = 0; i < 6; i++)
        {
            if (dutchList[i]->getDutchUUID() == j["dutch_uuid"])
            {
                index = i;
                break;
            }
        }

        vector<string> senders = j["user_list"];
        string senderString = "";
        for (string sender : senders)
        {
            senderString += sender + ", ";
        }
        senderString.erase(senderString.end() - 2, senderString.end());
        dutchList[index]->getSendUserList()->setState(senderString);

        int targetAmount = j["total_balence"];
        int currentAmount = j["current_balence"];

        dutchList[index]->getTargetAmount()->setState("$" + to_string(currentAmount) + " / $" + to_string(targetAmount));
    }
    catch (json::parse_error &e)
    {
        cout << "ReceivePage::getDutchInfoHandler: parse error" << e.what() << endl;
    }
    emscripten_fetch_close(fetch);
}

EMSCRIPTEN_BINDINGS(ReceivePage)
{
    emscripten::function("ReceivePage.receiveDutchButtonHandler", &ReceivePage::receiveDutchButtonHandler);
    emscripten::function("ReceivePage.nextButtonHandler", &ReceivePage::nextButtonHandler);
    emscripten::function("ReceivePage.prevButtonHandler", &ReceivePage::prevButtonHandler);
}