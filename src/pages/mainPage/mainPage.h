#include "../page/page.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#pragma once

class MainPage : public Element {
    State<string>* backwardTextState;
    State<string>* logoutTextState;
    State<string>* addMoneyTextState;
    State<string>* sendTextState;

    Flex* container;
    Flex* body;
    Flex* moneyContainer;

    Button* backwardButton;
    Button* logoutButton;
    Button* addMoneyButton;
    Button* sendButton;

    public:
        MainPage();
        ~MainPage();
};