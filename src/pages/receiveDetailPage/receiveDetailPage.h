#pragma once

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"

class ReceiveDetailPage : public Element
{

    State<string> *charge;   // 더치 금액
    State<bool> *isComplete; // 더치 완료 여부

    Button *completeButton; // 더치 완료 버튼

    Text *chargeText;                  // 더치 금액 보여주기
    Text *receiveUserText;             // 받는 사람 보여주기
    std::unique_ptr<Text> billTitle;   // 영수증 제목
    std::unique_ptr<Text> chargeLabel; // 더치 금액 라벨

    std::unique_ptr<Flex> billContainer;       // 영수증 컨테이너
    std::unique_ptr<Element> billUpper;        // 영수증 상단
    std::unique_ptr<Element> billUpperDivider; // 영수증 상단 구분선
    std::unique_ptr<Element> billLower;        // 영수증 하단
    std::unique_ptr<Element> billLowerDivider; // 영수증 하단 구분선

    static ReceiveDetailPage *instance;
    ReceiveDetailPage();

public:
    ~ReceiveDetailPage();

    static ReceiveDetailPage *getInstance();
    static void completeButtonHandler(emscripten::val event);
};