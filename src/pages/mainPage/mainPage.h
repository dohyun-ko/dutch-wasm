#pragma once

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"

class MainPage : public Element
{

    State<string> *myBalance;

    Element *container;
    Flex *leftSide;
    Flex *rightSide;
    Text *balanceText;
    Text *myBalanceText;

    Button *sendButton;
    Button *receiveButton;
    Button *loginButton; // global state에 유저 정보가 있으면 이 버튼을 안보이게 해야함 - branch 20 참고

    static MainPage *instance;
    MainPage();

public:
    ~MainPage();

    static MainPage *getInstance();
};