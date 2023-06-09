#include "makeDutchPage.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <emscripten/bind.h>
#include <algorithm>

#include "../../globalState/userState/userState.h"
#include "../../router/Router.h"

using json = nlohmann::json;

MakeDutchPage *MakeDutchPage::instance = nullptr;
Button *MakeDutchPage::addUserButtons[8] = {nullptr};
Button *MakeDutchPage::subUserButtons[4] = {nullptr};
Element *MakeDutchPage::userItems[8] = {nullptr};
Element *MakeDutchPage::sendUserItems[4] = {nullptr};
State<vector<string>> *MakeDutchPage::sendUserUUIDs = new State<vector<string>>({});
State<vector<string>> *MakeDutchPage::userUUIDs = new State<vector<string>>({});
State<string> *MakeDutchPage::sendUsernames[4] = {new State<string>(""), new State<string>(""), new State<string>(""), new State<string>("")};
State<string> *MakeDutchPage::usernames[8] = {new State<string>(""), new State<string>(""), new State<string>(""), new State<string>(""), new State<string>(""), new State<string>(""), new State<string>(""), new State<string>("")};
State<string> *MakeDutchPage::charge = new State<string>("0");
State<string> *MakeDutchPage::dutchType = new State<string>("normal");

MakeDutchPage::MakeDutchPage() : Element("div")
{

    sendUserUUIDs->setState({});
    userUUIDs->setState({});
    for (size_t i = 0; i < 4; i++)
    {
        sendUsernames[i]->setState("");
    }
    for (size_t i = 0; i < 8; i++)
    {
        usernames[i]->setState("");
    }
    charge->setState("0");
    dutchType->setState("normal");

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

    billTitle = new Text(new State<string>("Make Dutch"));
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
    sendUserLabel = new Text(new State<string>("Dutchers: "));
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

    for (size_t i = 0; i < 4; i++)
    {
        Style *tempUserItemStyle = new Style();
        tempUserItemStyle
            ->setWidth("calc(100% - 20px)")
            .setHeight("30px")
            .setPadding("5px 10px")
            .setBackground(Style::primary)
            .setBorderRadius("5px")
            .setBoxShadow("2px 2px 5px 0px rgba(0,0,0,0.3)")
            .setDisplay("flex")
            .setJustifyContent("space-between")
            .setAlignItems("center");
        sendUserItems[i] = new Element("div", tempUserItemStyle);
        subUserButtons[i] = new Button(new State<string>("X"), subUserButtonStyle, "subUserButton" + to_string(i));
        sendUserItems[i]->appendChildren({new Text(sendUsernames[i], userItemNameStyle), subUserButtons[i]});
        sendUserContainer->appendChildren({sendUserItems[i]});
        sendUserItems[i]->getStyle().setDisplay("none");
        subUserButtons[i]->getElement().set("onclick", emscripten::val::module_property("MakeDutchPage.subUserButtonHandler"));
    }

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
    normalDutchRadio->getElement().set("onclick", emscripten::val::module_property("MakeDutchPage.dutchTypeRadioHandler"));
    raceDutchRadio = new Radio(new State<string>("race"), dutchType, nullptr, "raceDutchRadio");
    raceDutchRadio->getElement().set("onclick", emscripten::val::module_property("MakeDutchPage.dutchTypeRadioHandler"));
    relayDutchRadio = new Radio(new State<string>("relay"), dutchType, nullptr, "relayDutchRadio");
    relayDutchRadio->getElement().set("onclick", emscripten::val::module_property("MakeDutchPage.dutchTypeRadioHandler"));

    radioContainer->appendChildren({normalDutchRadio, raceDutchRadio, relayDutchRadio});

    makeButton = new Button(new State<string>("Make"), Style::defaultButtonStyle());
    billLower->appendChildren({radioContainer, makeButton});

    makeButton->getElement().set("onclick", emscripten::val::module_property("MakeDutchPage.makeButtonHandler"));

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

    for (size_t i = 0; i < 8; i++)
    {
        userItems[i] = new Element("div", userItemStyle);
        addUserButtons[i] = new Button(new State<string>("+"), addUserButtonStyle, "addUserButton" + to_string(i));
        userItems[i]->appendChildren({new Text(usernames[i], userItemNameStyle), addUserButtons[i]});
        userContainer->appendChildren({userItems[i]});
        addUserButtons[i]->getElement().set("onclick", emscripten::val::module_property("MakeDutchPage.addUserButtonHandler"));
    }

    MakeDutchPage::appendChildren({billContainer, userContainer});

    chargeInput->getElement().set("onchange", emscripten::val::module_property("MakeDutchPage.dutchBalanceInputHandler"));

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = getUsersNetworkHandler;

    emscripten_fetch(&attr, "http://13.124.243.56:8080/user/find/all");
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
    instance = nullptr;
}

void MakeDutchPage::getUsersNetworkHandler(emscripten_fetch_t *fetch)
{
    std::cout << "MakeDutchPage::getUsersNetworkHandler" << std::endl;
    std::cout << "status: " << fetch->status << std::endl;

    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        userUUIDs->setState(j["user_list"]);

        for (size_t i = 0; i < (userUUIDs->getValue().size() < 8 ? userUUIDs->getValue().size() : 8); i++)
        {
            emscripten_fetch_attr_t attr;
            emscripten_fetch_attr_init(&attr);
            strcpy(attr.requestMethod, "GET");
            attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
            attr.onsuccess = MakeDutchPage::getUserInfoNetworkHandler;

            string url = "http://13.124.243.56:8080/user/find?uuid=" + userUUIDs->getValue()[i];
            emscripten_fetch(&attr, url.c_str());
        }
    }
    catch (json::parse_error &e)
    {
        std::cout << "parsing error" << std::endl;
        std::cout << e.what() << std::endl;
    }
}

void MakeDutchPage::getUserInfoNetworkHandler(emscripten_fetch_t *fetch)
{
    std::cout << "MakeDutchPage::getUserInfoNetworkHandler" << std::endl;
    std::cout << "status: " << fetch->status << std::endl;

    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        int index = 0;
        for (size_t i = 0; i < userUUIDs->getValue().size(); i++)
        {
            if (userUUIDs->getValue()[i] == j["uuid"])
            {
                index = i;
                break;
            }
        }
        string username = j["username"];
        usernames[index]->setState(username);
    }
    catch (json::parse_error &e)
    {
        std::cout << "parsing error" << std::endl;
        std::cout << e.what() << std::endl;
    }
}

void MakeDutchPage::addUserButtonHandler(emscripten::val event)
{
    std::cout << "MakeDutchPage::addUserButtonHandler" << std::endl;
    std::cout << event["target"]["id"].as<string>() << std::endl;

    // 버튼 아이디 추출
    string buttonId = event["target"]["id"].as<string>();
    buttonId.erase(buttonId.begin(), buttonId.begin() + 13);
    std::stringstream ssInt(buttonId);
    int index = 0;
    ssInt >> index;

    // 추가 조건
    if (index >= userUUIDs->getValue().size())
    {
        return;
    }
    if (sendUsernames[3]->getValue() != "")
    {
        return;
    }
    string UUID = userUUIDs->getValue()[index];
    cout << UUID << endl;
    vector<string> tempSendUserUUIDs = sendUserUUIDs->getValue();
    if (find(tempSendUserUUIDs.begin(), tempSendUserUUIDs.end(), UUID) == tempSendUserUUIDs.end())
    {
        std::cout << "add" << std::endl;
    }
    else
    {
        std::cout << "alread exist" << std::endl;
        return;
    }

    // sendUserUUIDs, sendUsernames에 추가
    tempSendUserUUIDs.push_back(UUID);
    sendUserUUIDs->setState(tempSendUserUUIDs);

    string username = usernames[index]->getValue();
    for (size_t i = 0; i < 4; i++)
    {
        if (!(sendUsernames[i]->getValue().empty()))
        {
            continue;
        }
        else
        {
            sendUserItems[i]->getStyle().setDisplay("flex");
            sendUsernames[i]->setState(username);
            break;
        }
    }
}

void MakeDutchPage::subUserButtonHandler(emscripten::val event)
{
    std::cout << "MakeDutchPage::subUserButtonHandler" << std::endl;
    std::cout << event["target"]["id"].as<string>() << std::endl;

    // 버튼 아이디 추출
    string buttonId = event["target"]["id"].as<string>();
    buttonId.erase(buttonId.begin(), buttonId.begin() + 13);
    std::stringstream ssInt(buttonId);
    int index = 0;
    ssInt >> index;

    // sendUserUUIDs, sendUsernames에서 제거
    vector<string> tempSendUserUUIDs = sendUserUUIDs->getValue();
    tempSendUserUUIDs.erase(tempSendUserUUIDs.begin() + index);
    sendUserUUIDs->setState(tempSendUserUUIDs);

    for (size_t i = 0; i < 4; i++)
    {
        if (i == index)
        {
            sendUsernames[i]->setState("");
        }
        else if (i > index)
        {
            sendUsernames[i - 1]->setState(sendUsernames[i]->getValue());
            sendUsernames[i]->setState("");
        }
    }
    for (size_t i = 0; i < 4; i++)
    {
        if (sendUsernames[i]->getValue() == "")
        {
            sendUserItems[i]->getStyle().setDisplay("none");
        }
    }
}

void MakeDutchPage::dutchTypeRadioHandler(emscripten::val event)
{
    std::cout << "MakeDutchPage::dutchTypeRadioHandler" << std::endl;
    string radioType = "";
    try
    {
        radioType = event["target"]["value"].as<string>();
    }
    catch (exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << radioType << std::endl;

    dutchType->setState(radioType);
}

void MakeDutchPage::dutchBalanceInputHandler(emscripten::val event)
{
    std::cout << "MakeDutchPage::dutchBalanceInputHandler" << std::endl;
    string inputCharge = event["target"]["value"].as<string>();
    MakeDutchPage::charge->setState(inputCharge);
}

void MakeDutchPage::makeButtonHandler(emscripten::val event)
{
    std::cout << "MakeDutchPage::makeButtonHandler" << std::endl;
    int number=0;
    if (sendUsernames[0]->getValue() == "")
    {
        return;
    }
    string queryUserList = "";
    for (size_t i = 0; i < 4; i++)
    {
        if (sendUsernames[i]->getValue() == "")
        {
            break;
        }
        queryUserList += sendUserUUIDs->getValue()[i] + ",";
        number++;
    }
    queryUserList.pop_back();
    
    int chargeNumber;
    string chargeString = MakeDutchPage::charge->getValue();
    std::stringstream ssInt(chargeString);
    ssInt >> chargeNumber;

    if (chargeNumber%number != 0 || chargeNumber == 0)
    {
        return;
    }


    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = MakeDutchPage::makeDutchNetworkHandler;

    string url = "http://13.124.243.56:8080/dutch/" + dutchType->getValue() + "?owner=" + UserState::getInstance()->getCurrentUser()->getValue().getUUID() + "&target_balance="+ charge->getValue() +"&user_list=" + queryUserList;
    emscripten_fetch(&attr, url.c_str());
}

void MakeDutchPage::makeDutchNetworkHandler(emscripten_fetch_t *fetch)
{
    std::cout << "MakeDutchPage::makeDutchNetworkHandler" << std::endl;
    Router::getInstance()->navigate("/main");
}

EMSCRIPTEN_BINDINGS(MakeDutchPage)
{
    emscripten::function("MakeDutchPage.addUserButtonHandler", &MakeDutchPage::addUserButtonHandler);
    emscripten::function("MakeDutchPage.dutchBalanceInputHandler", &MakeDutchPage::dutchBalanceInputHandler);
    emscripten::function("MakeDutchPage.subUserButtonHandler", &MakeDutchPage::subUserButtonHandler);
    emscripten::function("MakeDutchPage.dutchTypeRadioHandler", &MakeDutchPage::dutchTypeRadioHandler);
    emscripten::function("MakeDutchPage.makeButtonHandler", &MakeDutchPage::makeButtonHandler);
}