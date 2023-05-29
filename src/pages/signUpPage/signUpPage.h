#pragma once 
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

class SignUpPage: public Page {
    State<string>* webTextState;
    State<string>* loginText;
    Flex* container;
    Button* loginButton;
    Button* webButton;
    Input* usernameInput;
    Input* passwordInput;
    Input* nicknameInput;
    public:
        SignUpPage(val root);
        ~SignUpPage();
        void render();
        void remove();
};