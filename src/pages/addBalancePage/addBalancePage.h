#pragma once

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"
#include "../../components/input/Input.h"

class AddBalancePage : public Element
{
    State<string> *myBalance;  // 내 잔액
    State<string> *addBalance; // 추가할 잔액

    Flex *container;      // 컨테이너
    Element *balanceGrid; // 잔액 그리드

    Button *addButton; // 추가하기 버튼

    Input *addBalanceInput; // 추가할 잔액 입력창

    Text *myBalanceText; // 내 잔액 텍스트
    Text *myBalanceLabel;
    Text *addBalanceLabel;

    Style *textStyle;

    static AddBalancePage *instance;
    AddBalancePage();

public:
    ~AddBalancePage();

    static AddBalancePage *getInstance();
};