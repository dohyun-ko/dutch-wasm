#pragma once

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"

//global state로 sendDutchPage에게 Dutch의 UUID or dutch의 모든 정보 전달해야함
class SendPage : public Element {

    Button* sendDutchButtons[8]; //보낼 수 있는 더치 리스트 클릭시 해당 sendDutchPage로 이동 (event의 target을 이용해서 더치 uuid를 가져올 수 있도록 로직 구성예정)
    Button* nextButton; //8개 이상의 더치가 있을 경우 다음 페이지로 넘어가는 버튼
    Button* prevButton; //8개 이상의 더치가 있을 경우 이전 페이지로 넘어가는 버튼

    static SendPage* instance;
    SendPage();

    public:
        ~SendPage();

        static SendPage* getInstance();
        static void nextButtonHandler(emscripten::val event);
        static void prevButtonHandler(emscripten::val event);
        static void sendDutchButtonHandler(emscripten::val event);
};
