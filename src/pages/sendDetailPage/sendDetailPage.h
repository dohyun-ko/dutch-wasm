#pragma once

#include <iostream>
#include <emscripten/fetch.h>

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"
#include "../../components/input/Input.h"
#include "../../globalState/sendDutchState/sendDutchState.h"
#include "../../globalState/userState/userState.h"

class SendDetailPage : public Element
{

    State<std::string> *myBalance;  // 내 잔액

    Text *chargeText;       // 더치 금액 보여주기
    Text *receiveUserText;  // 받는 사람 보여주기
    Text *myBalanceText;    // 내 잔액 보여주기
    Text *sendChargeText;   // 보내는 금액 보여주기
    Input *sendChargeInput; // 보내는 금액 입력창

    Button *sendButton; // 더치 보내기 버튼

    Input *input; // 더치 금액 입력창 (normal Dutch의 경우에는 보이지 않음)

    Flex *billContainer;       // 영수증 컨테이너
    Element *billUpper;        // 영수증 상단
    Element *billUpperDivider; // 영수증 상단 구분선
    Element *billLower;        // 영수증 하단
    Element *billLowerDivider; // 영수증 하단 구분선

    Text *billTitle;        // 영수증 제목
    Text *chargeLabel;      // 더치 금액 라벨
    Text *receiveUserLabel; // 받는 사람 라벨
    Text *myBalanceLabel;   // 내 잔액 라벨
    Text *sendChargeLabel;  // 보내는 금액 라벨

    static SendDetailPage *instance;
    SendDetailPage();

public:
    ~SendDetailPage();

    static State<string> *nowUUID;
    static State<string> *charge; //더치 금액
    static State<string> *sendCharge; //보낼 금액
    static State<string> *receiveUser; //받는 사람
    static bool isSended;
    static SendDetailPage *getInstance();
    static void sendButtonHandler(emscripten::val event);
    static void inputHandler(emscripten::val event);
    static void sendNetworkHandler(emscripten_fetch_t *fetch);
    static void getDutchNetworkHandler(emscripten_fetch_t *fetch);
};