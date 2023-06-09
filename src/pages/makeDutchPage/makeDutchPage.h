#pragma once

#include <vector>

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"
#include "../../components/state/State.cpp"
#include "../../components/input/Input.h"
#include "../../components/radio/Radio.h"

class MakeDutchPage : public Element
{

    State<vector<string>> *sendUsers;
    State<string> *charge; // to @siwonpada - Input과 함께 사용하려면 string이어야 하기에 변경 by @Dohyun-Ko
    State<string> *dutchType;

    Button *makeButton;
    Button *addUserButtons[8]; // 전체 유저를 가져오는 버튼 (event의 target을 이용해서 유저 uuid를 가져올 수 있도록 로직 구성예정)
    Button *subUserButtons[4]; // 선택된 유저를 제거하는 버튼 (event의 target을 이용해서 유저 uuid를 가져올 수 있도록 로직 구성예정)

    Input *dutchBalenceInput;

    Text *chargeText;      // 더치 금액 보여주기
    Text *receiveUserText; // 받는 사람 보여주기

    Input *chargeInput; // 더치 금액 입력창
    Radio *normalDutchRadio;
    Radio *raceDutchRadio;
    Radio *relayDutchRadio;

    Flex *billContainer;       // 영수증 컨테이너
    Element *billUpper;        // 영수증 상단
    Element *billUpperDivider; // 영수증 상단 구분선
    Element *billLower;        // 영수증 하단
    Element *billLowerDivider; // 영수증 하단 구분선
    Flex *sendUserContainer;
    Flex *userContainer;
    Flex *radioContainer;

    Text *billTitle;     // 영수증 제목
    Text *chargeLabel;   // 더치 금액 라벨
    Text *sendUserLabel; // 받는 사람 라벨

    Element *userItems[8];
    Element *sendUserItems[4];

    Style *userItemStyle;
    Style *subUserButtonStyle;
    Style *addUserButtonStyle;
    Style *userItemNameStyle;

    static MakeDutchPage *instance;
    MakeDutchPage();

public:
    ~MakeDutchPage();

    static MakeDutchPage *getInstance();
    static void makeButtonHandler(emscripten::val event);
    static void addUserButtonHandler(emscripten::val event);
    static void subUserButtonHandler(emscripten::val event);
    static void dutchBalanceInputHandler(emscripten::val event);
};