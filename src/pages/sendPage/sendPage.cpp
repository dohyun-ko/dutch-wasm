#include "sendPage.h"

#include <emscripten/bind.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <sstream>

#include "../../components/style/Style.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../router/Router.h"
#include "../../utils/Constants.h"

using json = nlohmann::json;

SendPageStates::SendPageStates()
{
    this->receiveUser = new State<string>("");
    this->sendAmount = new State<string>("");
    this->dutchUUID = "";
}

SendPageStates::~SendPageStates()
{
    delete this->receiveUser;
    delete this->sendAmount;
}

State<string> *SendPageStates::getReceiveUser()
{
    return this->receiveUser;
}

State<string> *SendPageStates::getSendAmount()
{
    return this->sendAmount;
}

string SendPageStates::getDutchUUID()
{
    return this->dutchUUID;
}

void SendPageStates::setDutchUUID(string uuid)
{
    this->dutchUUID = uuid;
}

SendPage *SendPage::instance = nullptr;
SendPageStates *SendPage::dutchList[6] = {new SendPageStates(), new SendPageStates(), new SendPageStates(), new SendPageStates(), new SendPageStates(), new SendPageStates()};
State<vector<string>> *SendPage::dutchUUIDList = SendDutchState::getInstance()->getSendUUIDs();
int SendPage::currentPageNumber = 0;

SendPage::SendPage() : Element("div")
{
    currentPageNumber = 0;
    SendPage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("row")
        .setAlignItems("center")
        .setJustifyContent("center");

    prevButton = new Button(new State<string>("⬅"));
    nextButton = new Button(new State<string>("➡"));

    dutchItemContainer = std::make_unique<Element>("div");
    dutchItemContainer->getStyle()
        .setWidth("70%")
        .setHeight("50%")
        .setDisplay("grid")
        .setGridTemplateColumns("repeat(3, 1fr)")
        .setGap("25px");

    dutchItemWrapperStyle = std::make_shared<Style>();
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

    dutchItemUserNameStyle = std::make_shared<Style>();
    dutchItemUserNameStyle->setFontSize("16px")
        .setFontWeight("600")
        .setWidth("calc(100\% - 20px)")
        .setTextAlign("left")
        .setBackground(Style::primary)
        .setPadding("10px 10px 0px 10px")
        .setMargin("0")
        .setHeight("20%");

    dutchItemChargeStyle = std::make_shared<Style>();
    dutchItemChargeStyle->setFontSize("16px")
        .setFontWeight("400")
        .setWidth("calc(100\% - 20px)")
        .setTextAlign("right")
        .setPadding("0px 10px 10px 10px")
        .setMargin("0")
        .setHeight("20%");

    dutchItemTitleStyle = std::make_shared<Style>();
    dutchItemTitleStyle->setFontSize("16px")
        .setBorder("none")
        .setBorderRadius("8px")
        .setFontSize("20px")
        .setFontWeight("bold")
        .setColor(Style::primaryVariant)
        .setMargin("0");

    string username = UserState::getInstance()->getCurrentUser()->getValue().getUsername();

    dutchItemButtonStyle = std::make_shared<Style>();
    dutchItemButtonStyle
        ->setBorder("none")
        .setBorderRadius("6px")
        .setPadding("5px 15px")
        .setMargin("0")
        .setBackground(Style::primaryVariant);

    dutchItemButtonTextState = std::make_shared<State<std::string>>("View Detail");

    dutchItem1 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem1");

    dutchItem2 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem2");

    dutchItem3 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem3");

    dutchItem4 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem4");

    dutchItem5 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem5");

    dutchItem6 = new Button(dutchItemButtonTextState, dutchItemButtonStyle, "dutchItem6");

    dutchItemWrapper1 = std::make_unique<Element>("div", dutchItemWrapperStyle);
    dutchItemWrapper1->appendChildren({new Text(dutchList[0]->getReceiveUser(), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(dutchList[0]->getSendAmount(), dutchItemChargeStyle),
                                       dutchItem1});

    dutchItemWrapper2 = std::make_unique<Element>("div", dutchItemWrapperStyle);
    dutchItemWrapper2->appendChildren({new Text(dutchList[1]->getReceiveUser(), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(dutchList[1]->getSendAmount(), dutchItemChargeStyle),
                                       dutchItem2});

    dutchItemWrapper3 = std::make_unique<Element>("div", dutchItemWrapperStyle);
    dutchItemWrapper3->appendChildren({new Text(dutchList[2]->getReceiveUser(), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(dutchList[2]->getSendAmount(), dutchItemChargeStyle),
                                       dutchItem3});

    dutchItemWrapper4 = std::make_unique<Element>("div", dutchItemWrapperStyle);
    dutchItemWrapper4->appendChildren({new Text(dutchList[3]->getReceiveUser(), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(dutchList[3]->getSendAmount(), dutchItemChargeStyle),
                                       dutchItem4});

    dutchItemWrapper5 = std::make_unique<Element>("div", dutchItemWrapperStyle);
    dutchItemWrapper5->appendChildren({new Text(dutchList[4]->getReceiveUser(), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(dutchList[4]->getSendAmount(), dutchItemChargeStyle),
                                       dutchItem5});

    dutchItemWrapper6 = std::make_unique<Element>("div", dutchItemWrapperStyle);
    dutchItemWrapper6->appendChildren({new Text(dutchList[5]->getReceiveUser(), dutchItemTitleStyle),
                                       new Text(new State<string>(username), dutchItemUserNameStyle),
                                       new Text(dutchList[5]->getSendAmount(), dutchItemChargeStyle),
                                       dutchItem6});

    dutchItemContainer->appendChildren({dutchItemWrapper1.get(),
                                        dutchItemWrapper2.get(),
                                        dutchItemWrapper3.get(),
                                        dutchItemWrapper4.get(),
                                        dutchItemWrapper5.get(),
                                        dutchItemWrapper6.get()});

    SendPage::appendChildren({prevButton, dutchItemContainer.get(), nextButton});

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

    string url = Constants::API_URL + "/dutch/all?user_uuid=" + UserState::getInstance()->getCurrentUser()->getValue().getUUID();
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

    delete nextButton;
    delete prevButton;
    delete dutchItem1;
    delete dutchItem2;
    delete dutchItem3;
    delete dutchItem4;
    delete dutchItem5;
    delete dutchItem6;
}

void SendPage::sendDutchButtonHandler(emscripten::val event)
{
    std::cout << "SendPage::sendDutchButtonHandler" << std::endl;
    string buttonId = event["target"]["id"].as<string>();
    buttonId.erase(buttonId.begin(), buttonId.begin() + 9);
    std::stringstream ssInt(buttonId);
    int index = 0;
    ssInt >> index;
    index--;

    SendDutchState::getInstance()->getNowUUID()->setState(dutchList[index]->getDutchUUID());

    Router::getInstance()->navigate("/sendDetail");
}

// 나에게 있는 dutch의 리스트만 받아서 글로벌 스테이트에 저장
void SendPage::getDutchListHandler(emscripten_fetch_t *fetch)
{
    std::cout << "SendPage::getDutchListHandler" << std::endl;
    std::cout << "status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        dutchUUIDList->setState(j["dutch_target_list"]);
        for (size_t i = 0; i < (dutchUUIDList->getValue().size() < 6 ? dutchUUIDList->getValue().size() : 6); i++)
        {
            std::cout << "SendDutchList: " << dutchUUIDList->getValue()[i] << std::endl;
            dutchList[i]->setDutchUUID(dutchUUIDList->getValue()[i]);

            emscripten_fetch_attr_t dutchInfoFetchAttr;
            emscripten_fetch_attr_init(&dutchInfoFetchAttr);
            strcpy(dutchInfoFetchAttr.requestMethod, "GET");
            dutchInfoFetchAttr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
            dutchInfoFetchAttr.onsuccess = SendPage::getDutchInfoHandler;

            string url = Constants::API_URL + "/dutch?dutch_uuid=" + dutchUUIDList->getValue()[i];
            emscripten_fetch(&dutchInfoFetchAttr, url.c_str());
        }
    }
    catch (json::parse_error &e)
    {
        cout << "SendPage::getDutchListHandler: parse error: " << e.what() << endl;
    }
    emscripten_fetch_close(fetch);
}

// 각 dutch의 정보를 받아서 화면에 표시
void SendPage::getDutchInfoHandler(emscripten_fetch_t *fetch)
{
    std::cout << "SendPage::getDutchInfoHandler" << std::endl;
    std::cout << "status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        // dutchUUID로 dutchList에서 index 찾기
        int index = 0;
        for (size_t i = 0; i < 6; i++)
        {
            if (dutchList[i]->getDutchUUID() == j["dutch_uuid"])
            {
                index = i;
                break;
            }
        }

        // 소유자 확인
        string receiver = j["owner_name"];
        dutchList[index]->getReceiveUser()->setState("Dutch by " + receiver);

        // dutch에 돈을 냈는지 확인
        vector<string> sendUserList = j["send_user_list"];
        std::cout << sendUserList[0] << ":::" << UserState::getInstance()->getCurrentUser()->getValue().getUUID() << std::endl;
        if (find(sendUserList.begin(), sendUserList.end(), UserState::getInstance()->getCurrentUser()->getValue().getUUID()) == sendUserList.end())
        {
            // dutchList에 정보 저장
            int total_charge = j["target_balance"];
            int charge = total_charge / j["user_list"].size(); // 각자 내야하는 금액(normal dutch 기준)
            dutchList[index]->getSendAmount()->setState("$" + to_string(charge));
        }
        else
        {
            dutchList[index]->getSendAmount()->setState("Completed");
        }
    }
    catch (json::parse_error &e)
    {
        cout << "SendPage::getDutchInfoHandler: parse error: " << e.what() << endl;
    }
    emscripten_fetch_close(fetch);
}

// 다음 버튼
void SendPage::nextButtonHandler(emscripten::val event)
{
    cout << "SendPage::nextButtonHandler" << endl;
    if (currentPageNumber * 6 + 6 >= dutchUUIDList->getValue().size())
        return;
    currentPageNumber++;

    for (size_t i = 0; i < 6; i++)
    {
        if (dutchUUIDList->getValue().size() <= currentPageNumber * 6 + i)
        {
            dutchList[i]->getSendAmount()->setState("");
            dutchList[i]->getReceiveUser()->setState("");
            continue;
        }
        std::cout << "SendDutchList: " << SendPage::dutchUUIDList->getValue()[i + currentPageNumber * 6] << std::endl;
        dutchList[i]->setDutchUUID(dutchUUIDList->getValue()[i + currentPageNumber * 6]);

        emscripten_fetch_attr_t dutchInfoFetchAttr;
        emscripten_fetch_attr_init(&dutchInfoFetchAttr);
        strcpy(dutchInfoFetchAttr.requestMethod, "GET");
        dutchInfoFetchAttr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        dutchInfoFetchAttr.onsuccess = SendPage::getDutchInfoHandler;

        string url = Constants::API_URL + "/dutch?dutch_uuid=" + SendPage::dutchUUIDList->getValue()[i + currentPageNumber * 6];
        emscripten_fetch(&dutchInfoFetchAttr, url.c_str());
    }
}

void SendPage::prevButtonHandler(emscripten::val event)
{
    cout << "SendPage::prevButtonHandler" << endl;
    if (currentPageNumber == 0)
        return;
    currentPageNumber--;

    for (size_t i = 0; i < 6; i++)
    {
        if (dutchUUIDList->getValue().size() <= currentPageNumber * 6 + i)
        {
            dutchList[i]->getSendAmount()->setState("");
            dutchList[i]->getReceiveUser()->setState("");
            continue;
        }
        std::cout << "SendDutchList: " << SendPage::dutchUUIDList->getValue()[i + currentPageNumber * 6] << std::endl;
        dutchList[i]->setDutchUUID(dutchUUIDList->getValue()[i + currentPageNumber * 6]);

        emscripten_fetch_attr_t dutchInfoFetchAttr;
        emscripten_fetch_attr_init(&dutchInfoFetchAttr);
        strcpy(dutchInfoFetchAttr.requestMethod, "GET");
        dutchInfoFetchAttr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        dutchInfoFetchAttr.onsuccess = SendPage::getDutchInfoHandler;

        string url = Constants::API_URL + "/dutch?dutch_uuid=" + SendPage::dutchUUIDList->getValue()[i + currentPageNumber * 6];
        emscripten_fetch(&dutchInfoFetchAttr, url.c_str());
    }
}

EMSCRIPTEN_BINDINGS(SendPage)
{
    emscripten::function("SendPage.sendDutchButtonHandler", &SendPage::sendDutchButtonHandler);
    emscripten::function("SendPage.nextButtonHandler", &SendPage::nextButtonHandler);
    emscripten::function("SendPage.prevButtonHandler", &SendPage::prevButtonHandler);
}