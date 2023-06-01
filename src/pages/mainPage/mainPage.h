#pragma once
#include "../page/page.h"


class MainPage: public Page {

    public:
        MainPage(val root);
        ~MainPage();
        void render();
        void remove();
};