#pragma once

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"
#include "../../components/input/Input.h"

class SendDutchPage : public Element
{

    State<int> *charge; // 더치 금액

    Text *chargeText;      // 더치 금액 보여주기
    Text *receiveUserText; // 받는 사람 보여주기

    Button *sendButton; // 더치 보내기 버튼

    Input *input; // 더치 금액 입력창 (normal Dutch의 경우에는 보이지 않음)

    Element *container;

    static SendDutchPage *instance;
    SendDutchPage();

public:
    ~SendDutchPage();

    static SendDutchPage *getInstance();
    static void sendButtonHandler(emscripten::val event);
};