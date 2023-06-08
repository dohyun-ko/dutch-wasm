#include "sendPage.h"

#include <emscripten/bind.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <algorithm>

#include "../../components/style/Style.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../router/Router.h"

using json = nlohmann::json;

SendPageStates::SendPageStates()
{
    this->receiveUser = new State<string>("Dutch by");
    this->sendAmount = new State<string>("$0");
}

State<string>* SendPageStates::getReceiveUser()
{
    return this->receiveUser;
}

State<string>* SendPageStates::getSendAmount()
{
    return this->sendAmount;
}

string SendPageStates::getDutchReceiverUUID()
{
    return this->dutchReceiverUUID;
}

void SendPageStates::setDutchReceiverUUID(string uuid)
{
    this->dutchReceiverUUID = uuid;
}

SendPage *SendPage::instance = nullptr;
SendPageStates* SendPage::dutchList[6] = {new SendPageStates(), new SendPageStates(), new SendPageStates(), new SendPageStates(), new SendPageStates(), new SendPageStates()};
State<vector<string>> *SendPage::dutchUUIDList = SendDutchState::getInstance()->getSendUUIDs();


SendPage::SendPage() : Element("div")
{
    SendPage::getStyle()
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
    dutchItemUserNameStyle->setFontSize("16px")
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

    dutchItem1 = new Button(nullptr, dutchItemStyle, "dutchItem1");
    dutchItem1->appendChildren({new Text(dutchList[0]->getReceiveUser()),
                                new Text(new State<string>(username), dutchItemUserNameStyle),
                                new Text(dutchList[0]->getSendAmount(), dutchItemChargeStyle)});

    dutchItem2 = new Button(nullptr, dutchItemStyle,"dutchItem2");
    dutchItem2->appendChildren({new Text(dutchList[1]->getReceiveUser()),
                                new Text(new State<string>(username), dutchItemUserNameStyle),
                                new Text(dutchList[1]->getSendAmount(), dutchItemChargeStyle)});

    dutchItem3 = new Button(nullptr, dutchItemStyle, "dutchItem3");
    dutchItem3->appendChildren({new Text(dutchList[2]->getReceiveUser()),
                                new Text(new State<string>(username), dutchItemUserNameStyle),
                                new Text(dutchList[2]->getSendAmount(), dutchItemChargeStyle)});

    dutchItem4 = new Button(nullptr, dutchItemStyle, "dutchItem4");
    dutchItem4->appendChildren({new Text(dutchList[3]->getReceiveUser()),
                                new Text(new State<string>(username), dutchItemUserNameStyle),
                                new Text(dutchList[3]->getSendAmount(), dutchItemChargeStyle)});

    dutchItem5 = new Button(nullptr, dutchItemStyle, "dutchItem5");
    dutchItem5->appendChildren({new Text(dutchList[4]->getReceiveUser()),
                                new Text(new State<string>(username), dutchItemUserNameStyle),
                                new Text(dutchList[4]->getSendAmount(), dutchItemChargeStyle)});

    dutchItem6 = new Button(nullptr, dutchItemStyle, "dutchItem6");
    dutchItem6->appendChildren({new Text(dutchList[5]->getReceiveUser()),
                                new Text(new State<string>(username), dutchItemUserNameStyle),
                                new Text(dutchList[5]->getSendAmount(), dutchItemChargeStyle)});

    dutchItemContainer->appendChildren({dutchItem1, dutchItem2, dutchItem3, dutchItem4, dutchItem5, dutchItem6});

    SendPage::appendChildren({prevButton, dutchItemContainer, nextButton});

    nextButton->getElement().set("onclick", emscripten::val::module_property("SendPage.nextButtonHandler"));
    prevButton->getElement().set("onclick", emscripten::val::module_property("SendPage.prevButtonHandler"));
    dutchItem2->getElement().set("onclick", emscripten::val::module_property("SendPage.sendDutchButtonHandler"));
    dutchItem1->getElement().set("onclick", emscripten::val::module_property("SendPage.sendDutchButtonHandler"));
    dutchItem3->getElement().set("onclick", emscripten::val::module_property("SendPage.sendDutchButtonHandler"));
    dutchItem4->getElement().set("onclick", emscripten::val::module_property("SendPage.sendDutchButtonHandler"));
    dutchItem5->getElement().set("onclick", emscripten::val::module_property("SendPage.sendDutchButtonHandler"));
    dutchItem6->getElement().set("onclick", emscripten::val::module_property("SendPage.sendDutchButtonHandler"));

    emscripten_fetch_attr_t dutchListFetchAttr;
    emscripten_fetch_attr_init(&dutchListFetchAttr);
    strcpy(dutchListFetchAttr.requestMethod, "GET");
    dutchListFetchAttr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    dutchListFetchAttr.onsuccess = SendPage::getDutchListHandler;

    string url = "http://13.124.243.56:8080/dutch/normal/user?user_uuid=" + UserState::getInstance()->getCurrentUser()->getValue().getUUID();
    emscripten_fetch(&dutchListFetchAttr, url.c_str());
}

SendPage *SendPage::getInstance()
{
    if (SendPage::instance == nullptr)
    {
        SendPage::instance = new SendPage();
    }

    return SendPage::instance;
}

SendPage::~SendPage()
{
    SendPage::instance = nullptr;

    delete dutchItemContainer;
}

void SendPage::sendDutchButtonHandler(emscripten::val event)
{
    std::cout << "SendPage::sendDutchButtonHandler" << std::endl;
    std::cout << "event: " << event["target"]["id"].as<string>() << std::endl;
    Router::getInstance()->navigate("/sendDetail");
}

void SendPage::getDutchListHandler(emscripten_fetch_t *fetch)
{
    std::cout << "SendPage::getDutchListHandler" << std::endl;
    std::cout << "status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        dutchUUIDList->setState(j["dutch_target_list"]);
        for(size_t i =0; i<(dutchUUIDList->getValue().size() < 6 ? dutchUUIDList->getValue().size() : 6); i++){
            std::cout << "SendDutchList: " << dutchUUIDList->getValue()[i] << std::endl;
            emscripten_fetch_attr_t dutchInfoFetchAttr;
            emscripten_fetch_attr_init(&dutchInfoFetchAttr);
            strcpy(dutchInfoFetchAttr.requestMethod, "GET");
            dutchInfoFetchAttr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
            dutchInfoFetchAttr.onsuccess = SendPage::getDutchInfoHandler;

            string url = "http://13.124.243.56:8080/dutch/normal?dutch_uuid=" + dutchUUIDList->getValue()[i];
            emscripten_fetch(&dutchInfoFetchAttr, url.c_str());
        }
    } 
    catch (json::parse_error &e)
    {
        cout << "SendPage::getDutchListHandler: parse error: " << e.what() << endl;
    }
    emscripten_fetch_close(fetch);
}

void SendPage::getDutchInfoHandler(emscripten_fetch_t *fetch)
{
    std::cout << "SendPage::getDutchInfoHandler" << std::endl;
    std::cout << "status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        vector<string> v = dutchUUIDList->getValue();
        int total_charge = j["target_balance"];
        int charge = total_charge / j["user_list"].size();
        int index = find(v.begin(), v.end(), j["dutch_uuid"]) - v.begin();
        dutchList[index]->getSendAmount()->setState("$"+to_string(charge));
        string receiver = j["owner"];
        dutchList[index]->setDutchReceiverUUID(receiver);

        emscripten_fetch_attr_t dutchReceiverInfoFetchAttr;
        emscripten_fetch_attr_init(&dutchReceiverInfoFetchAttr);
        strcpy(dutchReceiverInfoFetchAttr.requestMethod, "GET");
        dutchReceiverInfoFetchAttr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        dutchReceiverInfoFetchAttr.onsuccess = SendPage::getDutchReceiverInfoHandler;

        string url = "http://13.124.243.56:8080/user/find?uuid=" + receiver;
        emscripten_fetch(&dutchReceiverInfoFetchAttr, url.c_str());
    }
    catch (json::parse_error &e)
    {
        cout << "SendPage::getDutchInfoHandler: parse error: " << e.what() << endl;
    }
    emscripten_fetch_close(fetch);
}

void SendPage::getDutchReceiverInfoHandler(emscripten_fetch_t *fetch)
{
    std::cout << "SendPage::getDutchReceiverInfoHandler" << std::endl;
    std::cout << "status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        string receiver = j["username"];
        string uuid = j["uuid"];
        for (size_t i = 0; i < 6; i++)
        {
            if (dutchList[i]->getDutchReceiverUUID() == uuid && dutchList[i]->getReceiveUser()->getValue()=="Dutch by")
            {
                dutchList[i]->getReceiveUser()->setState("Dutch by " + receiver);
                break;
            }
        }
    }
    catch (json::parse_error &e)
    {
        cout << "SendPage::getDutchReceiverInfoHandler: parse error: " << e.what() << endl;
    }
}

void SendPage::nextButtonHandler(emscripten::val event)
{
    cout << "SendPage::nextButtonHandler" << endl;
    vector<string> v = SendPage::dutchUUIDList->getValue();
    for(size_t i=0;i<6;i++){
        v.push_back(v.at(0));
        v.erase(v.begin());
    }
    SendPage::dutchUUIDList->setState(v);

    for(size_t i =0; i<(SendPage::dutchUUIDList->getValue().size() < 6 ? SendPage::dutchUUIDList->getValue().size() : 6); i++){
            std::cout << "SendDutchList: " << SendPage::dutchUUIDList->getValue()[i] << std::endl;
            emscripten_fetch_attr_t dutchInfoFetchAttr;
            emscripten_fetch_attr_init(&dutchInfoFetchAttr);
            strcpy(dutchInfoFetchAttr.requestMethod, "GET");
            dutchInfoFetchAttr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
            dutchInfoFetchAttr.onsuccess = SendPage::getDutchInfoHandler;

            string url = "http://13.124.243.56:8080/dutch/normal?dutch_uuid=" + SendPage::dutchUUIDList->getValue()[i];
            emscripten_fetch(&dutchInfoFetchAttr, url.c_str());
    }
}

void SendPage::prevButtonHandler(emscripten::val event)
{
    cout << "SendPage::prevButtonHandler" << endl;
    vector<string> v = SendPage::dutchUUIDList->getValue();
    for(size_t i=0;i<6;i++){
        v.insert(v.begin(), v.at(v.size()-1));
        v.pop_back();
    }
    SendPage::dutchUUIDList->setState(v);

    for(size_t i =0; i<(SendPage::dutchUUIDList->getValue().size() < 6 ? SendPage::dutchUUIDList->getValue().size() : 6); i++){
            std::cout << "SendDutchList: " << SendPage::dutchUUIDList->getValue()[i] << std::endl;
            emscripten_fetch_attr_t dutchInfoFetchAttr;
            emscripten_fetch_attr_init(&dutchInfoFetchAttr);
            strcpy(dutchInfoFetchAttr.requestMethod, "GET");
            dutchInfoFetchAttr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
            dutchInfoFetchAttr.onsuccess = SendPage::getDutchInfoHandler;

            string url = "http://13.124.243.56:8080/dutch/normal?dutch_uuid=" + SendPage::dutchUUIDList->getValue()[i];
            emscripten_fetch(&dutchInfoFetchAttr, url.c_str());
    }
}

EMSCRIPTEN_BINDINGS(SendPage)
{
    emscripten::function("SendPage.sendDutchButtonHandler", &SendPage::sendDutchButtonHandler);
    emscripten::function("SendPage.nextButtonHandler", &SendPage::nextButtonHandler);
    emscripten::function("SendPage.prevButtonHandler", &SendPage::prevButtonHandler);
}