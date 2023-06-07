#pragma once

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"
#include "../../components/input/Input.h"

class AddBalancePage : public Element {
    State<string> *myBalance; //내 잔액
    State<string> *addBalance; //추가할 잔액

    Button* addButton; //추가하기 버튼

    Input* addBalanceInput; //추가할 잔액 입력창

    static AddBalancePage* instance;
    AddBalancePage();

    public:
        ~AddBalancePage();

        static AddBalancePage* getInstance();
};