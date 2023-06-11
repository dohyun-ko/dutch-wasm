#include "sendDetailPage.h"

#include <emscripten/bind.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <algorithm>
#include <string>

#include "../../router/Router.h"

using json = nlohmann::json;

SendDetailPage *SendDetailPage::instance = nullptr;
bool SendDetailPage::isSended = false;
State<string> *SendDetailPage::nowUUID = SendDutchState::getInstance()->getNowUUID();
State<string> *SendDetailPage::charge = new State<string>("0");
State<string> *SendDetailPage::sendCharge = new State<string>("0");
State<string> *SendDetailPage::receiveUser = new State<string>("User Name");

SendDetailPage::SendDetailPage() : Element("div")
{
    myBalance = UserState::getInstance()->getBalanceState();

    SendDetailPage::getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center")
        .setJustifyContent("center");

    billContainer = new Flex("column", "center", "center", "10px");
    billContainer->getStyle()
        .setWidth("50%")
        .setHeight("50%")
        .setBackground(Style::primaryVariant)
        .setBorderRadius("10px");

    billTitle = new Text(new State<string>("Dutch Detail"));
    billTitle->getStyle()
        .setFontSize("24px")
        .setFontWeight("bold");

    billUpper = new Element("div");
    billUpper->getStyle()
        .setMargin("10px")
        .setDisplay("grid")
        .setGridTemplateColumns("100px 1fr")
        .setGap("10px");

    chargeLabel = new Text(new State<string>("Total Charge: "));
    chargeText = new Text(charge);
    receiveUserLabel = new Text(new State<string>("Receiver: "));
    receiveUserText = new Text(receiveUser);
    myBalanceLabel = new Text(new State<string>("My Balance: "));
    myBalanceText = new Text(myBalance);
    sendChargeLabel = new Text(new State<string>("Send Charge: "));
    sendChargeText = new Text(sendCharge);
    sendChargeInput = new Input(new State<string>("amount to send"), Style::defaultInputStyle()); // 조건부 렌더링

    billUpper->appendChildren({chargeLabel, chargeText, receiveUserLabel, receiveUserText, myBalanceLabel, myBalanceText, sendChargeLabel, sendChargeInput});

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

    sendButton = new Button(new State<string>("Send"), Style::defaultButtonStyle());

    billLower->appendChildren({sendButton});

    billContainer->appendChildren({billTitle, billUpperDivider, billUpper, billLowerDivider, billLower});

    SendDetailPage::appendChildren({billContainer});

    sendButton->getElement().set("onclick", emscripten::val::module_property("SendDetailPage.sendButtonHandler"));
    sendChargeInput->getElement().set("oninput", emscripten::val::module_property("SendDetailPage.inputHandler"));

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = SendDetailPage::getDutchNetworkHandler;

    string url = "http://13.124.243.56:8080/dutch/normal?dutch_uuid=" + nowUUID->getValue();
    emscripten_fetch(&attr, url.c_str());
}

SendDetailPage *SendDetailPage::getInstance()
{
    if (SendDetailPage::instance == nullptr)
    {
        SendDetailPage::instance = new SendDetailPage();
    }

    return SendDetailPage::instance;
}

SendDetailPage::~SendDetailPage()
{
    SendDetailPage::instance = nullptr;

    delete billContainer;
}

void SendDetailPage::sendButtonHandler(emscripten::val event)
{
    std::cout << "SendDetailPage.sendButtonHandler" << std::endl;
    std::cout << "sendCharge: " << sendCharge->getValue() << std::endl;
    string sendChargeStr = "$" + sendCharge->getValue();
    cout << sendChargeStr << endl;
    cout << charge->getValue() << endl;
    if (isSended)
    {
        emscripten_run_script("alert('already Sended this dutch')");
        return;
    }
    else if (sendChargeStr == charge->getValue())
    {
        std::cout << "sendChargeStr == charge->getValue()" << std::endl;
        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);
        strcpy(attr.requestMethod, "POST");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        attr.onsuccess = SendDetailPage::sendNetworkHandler;

        string url = "http://13.124.243.56:8080/dutch/normal/pay?dutch_uuid=" + nowUUID->getValue() + "&user_uuid=" + UserState::getInstance()->getCurrentUser()->getValue().getUUID();
        emscripten_fetch(&attr, url.c_str());
    }
    else
    {
        emscripten_run_script("alert('Please input correct amount to send')");
    }
}

void SendDetailPage::inputHandler(emscripten::val event)
{
    std::cout << "SendDetailPage.inputHandler" << std::endl;
    sendCharge->setState(event["target"]["value"].as<string>());
}

void SendDetailPage::getDutchNetworkHandler(emscripten_fetch_t *fetch)
{
    std::cout << "SendDetailPage.getDutchNetworkHandler" << std::endl;
    std::cout << "fetch->status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        int totalCharge = j["target_balance"];
        int charge = totalCharge / j["user_list"].size();
        SendDetailPage::charge->setState("$" + to_string(charge));
        string receiveUser = j["owner_name"];
        SendDetailPage::receiveUser->setState(receiveUser);

        vector<string> sendUserList = j["send_user_list"];
        if (find(sendUserList.begin(), sendUserList.end(), UserState::getInstance()->getCurrentUser()->getValue().getUUID()) == sendUserList.end())
        {
            std::cout << "not sended" << std::endl;
            isSended = false;
        }
        else
        {
            isSended = true;
            SendDetailPage::charge->setState("Completed");
        }
    }
    catch (json::parse_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    emscripten_fetch_close(fetch);
}

void SendDetailPage::sendNetworkHandler(emscripten_fetch_t *fetch)
{
    std::cout << "SendDetailPage.sendNetworkHandler" << std::endl;
    std::cout << "fetch->status: " << fetch->status << std::endl;

    emscripten_fetch_close(fetch);
    Router::getInstance()->navigate("back");
}

EMSCRIPTEN_BINDINGS(SendDetailPage)
{
    emscripten::function("SendDetailPage.sendButtonHandler", &SendDetailPage::sendButtonHandler);
    emscripten::function("SendDetailPage.inputHandler", &SendDetailPage::inputHandler);
}