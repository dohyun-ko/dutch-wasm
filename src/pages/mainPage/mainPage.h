#pragma once

#include <emscripten/fetch.h>

#include "../../components/element/Element.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/text/Text.h"
#include "../../core/user/user.h"

class MainPage : public Element
{
    std::unique_ptr<Element> container;
    std::unique_ptr<Flex> leftSide;
    std::unique_ptr<Flex> rightSide;
    std::shared_ptr<Text> balanceText;
    std::shared_ptr<Text> myBalanceText;
    std::shared_ptr<Text> loginSuccessText;

    Button *sendButton;
    Button *receiveButton;
    Button *loginButton;
    Button *makeButton;
    Button *makeDutchButton;
    Button *addBalanceButton;

    static MainPage *instance;
    MainPage();

public:
    ~MainPage();

    static State<User> *userState;
    static State<string> *loginState;
    static State<string> *balanceState;

    static MainPage *getInstance();
    static void sendButtonHandler(emscripten::val event);
    static void receiveButtonHandler(emscripten::val event);
    static void loginButtonHandler(emscripten::val event);
    static void makeDutchButtonHandler(emscripten::val event);
    static void addBalanceButtonHandler(emscripten::val event);
    static void notLoginedButtonHandler(emscripten::val event);
    static void getBalanceNetworkHandler(emscripten_fetch_t *fetch);
};