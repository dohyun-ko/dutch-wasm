#pragma once

#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"

class MainPage : public Element {

    State<string>* myBalance;

    Element* container;
    Flex* leftSide;
    Flex* rightSide;
    Text* balanceText;
    Text* myBalanceText;

    Button* sendButton;
    Button* receiveButton;

    static MainPage* instance;
    MainPage();

    public:
        ~MainPage();

        static MainPage* getInstance();
};