#pragma once

#include <emscripten.h>

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"

class ReceivePageStates {
    State<string> *sendUserList;
    State<string> *targetAmount;

    public:
        ReceivePageStates();
        State<string>* getSendUserList();
        State<string>* getTargetAmount();
};

class ReceivePage : public Element
{
    Button *nextButton;             // 8개 이상의 더치가 있을 경우 다음 페이지로 넘어가는 버튼
    Button *prevButton;             // 8개 이상의 더치가 있을 경우 이전 페이지로 넘어가는 버튼

    State<int> *currentPage = 0;

    Style *dutchItemStyle;
    Style *dutchItemUserNameStyle;
    Style *dutchItemChargeStyle;

// 받을 수 있는 더치 리스트 (event의 target을 이용해서 더치 uuid를 가져올 수 있도록 로직 구성예정)
    Button *dutchItem1;
    Button *dutchItem2;
    Button *dutchItem3;
    Button *dutchItem4;
    Button *dutchItem5;
    Button *dutchItem6;

    Element *dutchItemContainer;

    static ReceivePage *instance;
    ReceivePage();

public:
    ~ReceivePage();

    static ReceivePageStates *dutchList[6];
    static State<vector<string>> *dutchUUIDList;
    static ReceivePage *getInstance();
    static void nextButtonHandler(emscripten::val event);
    static void prevButtonHandler(emscripten::val event);
    static void receiveDutchButtonHandler(emscripten::val event);
};