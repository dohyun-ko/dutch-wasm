#pragma once 
#include <emscripten/fetch.h>
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/style/Style.h"
#include "../../components/text/Text.h"

class SignUpPage: public Element {
    State<string>* signUpTextState;
    State<string>* backwardTextState;
    Flex* container;
    Button* backwardButton;
    Button* signUpButton;
    Input* usernameInput;
    Input* passwordInput;
    Input* emailInput;
    Text* signUpText;

    static SignUpPage* instance;
    SignUpPage();

    public:
        static State<string>* usernameState;
        static State<string>* passwordState;
        static State<string>* emailState;
        static State<string>* signUpSuccessState;
        static void getUsername(emscripten::val event);
        static void getPassword(emscripten::val event);
        static void getEmail(emscripten::val event);
        static void SignUpButtonHander(emscripten::val event);
        static void SignUpNetworkHandler(emscripten_fetch_t *fetch);
        ~SignUpPage();

        static SignUpPage* getInstance();

        
};