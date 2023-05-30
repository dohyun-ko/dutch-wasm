#pragma once
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

class LoginPage: public Page {
    State<string>* loginTextState;
    State<string>* signUpTextState;
    State<string>* backwardTextState;
    Flex* header;
    Flex* container;
    Button* backwardButton;
    Button* loginButton;
    Button* signUpButton;
    Input* usernameInput;
    Input* passwordInput;
    public:
        LoginPage(val root);
        ~LoginPage();
        void render();
        void remove();
};