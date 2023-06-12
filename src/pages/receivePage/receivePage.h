#pragma once

#include <emscripten.h>
#include <emscripten/fetch.h>
#include <emscripten/bind.h>
#include <memory>

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"
#include "../../router/Router.h"

class ReceivePageStates {
    State<string> *sendUserList;
    State<string> *targetAmount;
    string dutchUUID;

    public:
        ReceivePageStates();
        ~ReceivePageStates();
        State<string>* getSendUserList();
        State<string>* getTargetAmount();
        string getDutchUUID();
        void setDutchUUID(string uuid);
};

class ReceivePage : public Element
{
    Button *prevButton; // 6개 이상의 더치가 있을 경우 이전 페이지로 넘어가는 버튼
    Button *nextButton; // 6개 이상의 더치가 있을 경우 다음 페이지로 넘어가는 버튼

    Style *dutchItemWrapperStyle;
    Style *dutchItemUserNameStyle;
    Style *dutchItemChargeStyle;
    Style *dutchItemButtonStyle;
    Style *dutchItemTitleStyle;

    Element *dutchItemWrapper1;
    Element *dutchItemWrapper2;
    Element *dutchItemWrapper3;
    Element *dutchItemWrapper4;
    Element *dutchItemWrapper5;
    Element *dutchItemWrapper6;

    // 받을 수 있는 더치 리스트 (event의 target을 이용해서 더치 uuid를 가져올 수 있도록 로직 구성예정)
    Button *dutchItem1;
    Button *dutchItem2;
    Button *dutchItem3;
    Button *dutchItem4;
    Button *dutchItem5;
    Button *dutchItem6;

    std::shared_ptr<State<std::string>> dutchItemButtonTextState;

    std::unique_ptr<Element> dutchItemContainer;

    static ReceivePage *instance;
    ReceivePage();

public:
    ~ReceivePage();

    static ReceivePageStates *dutchList[6];
    static State<vector<string>> *dutchUUIDList;
    static int currentPageNumber;
    static ReceivePage *getInstance();
    static void nextButtonHandler(emscripten::val event);
    static void prevButtonHandler(emscripten::val event);
    static void receiveDutchButtonHandler(emscripten::val event);
    static void getDutchListHandler(emscripten_fetch_t *fetch);
    static void getDutchInfoHandler(emscripten_fetch_t *fetch);

};