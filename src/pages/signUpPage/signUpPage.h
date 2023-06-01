#pragma once 
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

class SignUpPage: public Element {
    State<string>* signUpTextState;
    State<string>* backwardTextState;
    Flex* container;
    Button* backwardButton;
    Button* signUpButton;
    Input* usernameInput;
    Input* passwordInput;
    Input* emailInput;
    public:
        SignUpPage();
        ~SignUpPage();
};