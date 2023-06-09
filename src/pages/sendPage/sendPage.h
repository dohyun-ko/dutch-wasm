#pragma once

#include <emscripten/fetch.h>

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"
#include "../../components/state/State.cpp"
#include "../../globalState/sendDutchState/sendDutchState.h"
#include "../../globalState/userState/userState.h"

class SendPageStates
{
    State<string> *receiveUser;
    State<string> *sendAmount;
    string dutchUUID;

public:
    SendPageStates();
    ~SendPageStates();
    State<string> *getReceiveUser();
    State<string> *getSendAmount();
    string getDutchUUID();
    void setDutchUUID(string uuid);
};

// global state로 sendDutchPage에게 Dutch의 UUID or dutch의 모든 정보 전달해야함
class SendPage : public Element
{

    Button *nextButton; // 6개 이상의 더치가 있을 경우 다음 페이지로 넘어가는 버튼
    Button *prevButton; // 6개 이상의 더치가 있을 경우 이전 페이지로 넘어가는 버튼

    State<int> *currentPage = 0;

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

    // 보낼 수 있는 더치 리스트 클릭시 해당 sendDutchPage로 이동 (event의 target을 이용해서 더치 uuid를 가져올 수 있도록 로직 구성예정)
    Button *dutchItem1;
    Button *dutchItem2;
    Button *dutchItem3;
    Button *dutchItem4;
    Button *dutchItem5;
    Button *dutchItem6;

    State<std::string> *dutchItemButtonTextState;

    Element *dutchItemContainer;

    static SendPage *instance;
    SendPage();

public:
    ~SendPage();

    static SendPageStates *dutchList[6];
    static State<vector<string>> *dutchUUIDList;
    static int currentPageNumber;
    static SendPage *getInstance();
    static void nextButtonHandler(emscripten::val event);
    static void prevButtonHandler(emscripten::val event);
    static void sendDutchButtonHandler(emscripten::val event);
    static void getDutchListHandler(emscripten_fetch_t *fetch);
    static void getDutchInfoHandler(emscripten_fetch_t *fetch);;
};
