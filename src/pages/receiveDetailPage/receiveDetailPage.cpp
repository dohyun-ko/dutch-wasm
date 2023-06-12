#include "receiveDetailPage.h"
#include "../../components/style/Style.h"
#include <emscripten/bind.h>
#include <emscripten/fetch.h>
#include <nlohmann/json.hpp>
#include "../../utils/Constants.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include "../../router/Router.h"

using json = nlohmann::json;

ReceiveDetailPage *ReceiveDetailPage::instance = nullptr;

bool ReceiveDetailPage::isCompleted = false;
State<string> *ReceiveDetailPage::nowUUID = ReceiveDutchState::getInstance()->getNowUUID();
State<string> *ReceiveDetailPage::totalCharge = new State<string>("0");
State<string> *ReceiveDetailPage::currentCharge = new State<string>("0");

ReceiveDetailPage::ReceiveDetailPage() : Element("div")
{
    totalCharge = new State<string>("0");

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
    chargeText = new Text(totalCharge);

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

    completeButton->getElement().set("onclick", emscripten::val::module_property("SendDetailPage.sendButtonHandler"));

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = ReceiveDetailPage::getDutchNetworkHandler;

    string url = Constants::API_URL + "/dutch/normal?dutch_uuid=" + nowUUID->getValue();
    emscripten_fetch(&attr, url.c_str());
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

void ReceiveDetailPage::completeButtonHandler(emscripten::val event)
{
    std::cout << "ReceiveDetailPage.completeButtonHandler" << std::endl;

    if (isCompleted)
    {
        emscripten_run_script("alert('already Completed this dutch')");
        return;
    }

    std::cout << "sendChargeStr == charge->getValue()" << std::endl;
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = ReceiveDetailPage::completeNetworkHandler;

    string url = Constants::API_URL + "/dutch/normal/pay?dutch_uuid=" + nowUUID->getValue() + "&user_uuid=" + UserState::getInstance()->getCurrentUser()->getValue().getUUID();
    emscripten_fetch(&attr, url.c_str());
}

void ReceiveDetailPage::getDutchNetworkHandler(emscripten_fetch_t *fetch)
{
    std::cout << "SendDetailPage.getDutchNetworkHandler" << std::endl;
    std::cout << "fetch->status: " << fetch->status << std::endl;
    try
    {
        json j = json::parse(string(fetch->data, fetch->numBytes));
        int totalCharge = j["target_balance"];
        int currentCharege = j["current_balance"];
        ReceiveDetailPage::totalCharge->setState(to_string(totalCharge));
        ReceiveDetailPage::currentCharge->setState(to_string(currentCharege));
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

void ReceiveDetailPage::completeNetworkHandler(emscripten_fetch_t *fetch)
{
    std::cout << "ReceiveDetailPage.sendNetworkHandler" << std::endl;
    std::cout << "fetch->status: " << fetch->status << std::endl;

    emscripten_fetch_close(fetch);
    Router::getInstance()->navigate("back");
}

EMSCRIPTEN_BINDINGS(ReceiveDetailPage)
{
    emscripten::function("ReceiveDetailPage.completeButtonHandler", &ReceiveDetailPage::completeButtonHandler);
}