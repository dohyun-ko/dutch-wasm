#pragma once 
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

class SignUpPage: public Page {
    State<string>* signUpTextState;
    State<string>* backwardTextState;
    Flex* header;
    Flex* container;
    Button* backwardButton;
    Button* signUpButton;
    Input* usernameInput;
    Input* passwordInput;
    Input* emailInput;
    public:
        SignUpPage(val root);
        ~SignUpPage();
        void render() override;
        void remove() override;
};