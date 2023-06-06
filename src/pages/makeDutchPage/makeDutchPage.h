#pragma once

#include <vector>

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"
#include "../../components/state/State.cpp"
#include "../../components/input/Input.h"

class MakeDutchPage : public Element {
    
    State<vector<string>>* sendUsers;
    State<int>* dutchBalance;

    Button* makeButton;
    Button* addUserButtons[8]; //전체 유저를 가져오는 버튼 (event의 target을 이용해서 유저 uuid를 가져올 수 있도록 로직 구성예정)
    Button* subUserButtons[4]; //선택된 유저를 제거하는 버튼 (event의 target을 이용해서 유저 uuid를 가져올 수 있도록 로직 구성예정)

    Input* dutchbalenceInput;

    static MakeDutchPage* instance;
    MakeDutchPage();

    public: 
        ~MakeDutchPage();

        static MakeDutchPage* getInstance();
        static void makeButtonHandler(emscripten::val event);
        static void addUserButtonHandler(emscripten::val event);
        static void subUserButtonHandler(emscripten::val event);
        static void dutchBalanceInputHandler(emscripten::val event);
};