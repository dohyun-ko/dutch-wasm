#pragma once

#include <emscripten/bind.h>
#include <emscripten/fetch.h>
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/text/Text.h"
#include "../../core/user/user.h"

class LoginPage : public Element
{
    
    State<string> *loginTextState;
    State<string> *signUpTextState;

    Style* buttonStyle;

    Flex* container;

    Button* loginButton;
    Button* signUpButton;

    Input* usernameInput;
    Input* passwordInput;

    Text* loginText;

    static LoginPage* instance;
    LoginPage();

public:
    ~LoginPage();

    static State<string>* loginState;
    static State<User>* userState;
    static State<string>* usernameState;
    static State<string>* passwordState;

    static LoginPage* getInstance();

    static void LoginButtonHandler(emscripten::val event);
    static void SignUpButtonHandler(emscripten::val event);
    static void getUsername(emscripten::val event);
    static void getPassword(emscripten::val event);
    static void LoginSuccessHandler(emscripten_fetch_t *fetch);
    static void LoginfailedHandler(emscripten_fetch_t *fetch);
};
