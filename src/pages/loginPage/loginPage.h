#pragma once
#include <emscripten/bind.h>
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

class LoginPage : public Page
{
    State<string> *signUpTextState;
    State<string> *backwardTextState;

    Flex *header;
    Flex *container;

    Button *backwardButton;
    Button *loginButton;
    Button *signUpButton;

    Input *usernameInput;
    Input *passwordInput;

public:
    static State<string> *loginTextState;
    LoginPage(val root);
    ~LoginPage();
    void render() override;
    void remove() override;
    void setOnClick();
    static void LoginButtonHander(emscripten::val event);
    void SignUpButtonHander();
    void BackwardButtonHander();
};
