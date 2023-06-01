#pragma once
#include <emscripten/bind.h>
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

class LoginPage : public Element
{
    State<string> *signUpTextState;
    State<string> *backwardTextState;

    Style* buttonStyle;

    Flex* container;

    Button* backwardButton;
    Button* loginButton;
    Button* signUpButton;

    Input* usernameInput;
    Input* passwordInput;

public:
    static State<string> *loginTextState;
    LoginPage();
    ~LoginPage();

    static void LoginButtonHander(emscripten::val event);
    static void SignUpButtonHander(emscripten::val event);
    static void BackwardButtonHander(emscripten::val event);
};
