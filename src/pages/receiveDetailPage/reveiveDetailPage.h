#pragma once

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"

class ReceiveDetailPage : public Element {

    State<int> *charge; //더치 금액
    State<bool> *isComplete; //더치 완료 여부

    Button* completeButton; //더치 완료 버튼

    static ReceiveDetailPage* instance;
    ReceiveDetailPage();

    public:
        ~ReceiveDetailPage();

        static ReceiveDetailPage* getInstance();
        static void completeButtonHandler(emscripten::val event);
};