#pragma once
#include "../page/page.h"
#include "../../components/state/State.h"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

class LoginPage: public Page {
    State* webTextState;
    State* loginText;
    Flex* container;
    Button* loginButton;
    Button* webButton;
    Input* usernameInput;
    Input* passwordInput;
    public:
        LoginPage(val root);
        void render();
};