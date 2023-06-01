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

    static SignUpPage* instance;
    SignUpPage();

    public:
        static State<string>* usernameState;
        static State<string>* passwordState;
        static State<string>* emailState;
        static void getUsername(emscripten::val event);
        static void getPassword(emscripten::val event);
        static void getEmail(emscripten::val event);
        static void SignUpButtonHander(emscripten::val event);
        ~SignUpPage();

        static SignUpPage* getInstance();

        
};