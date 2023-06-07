#include "makeDutchPage.h"

MakeDutchPage* MakeDutchPage::instance = nullptr;

MakeDutchPage::MakeDutchPage() : Element("div") {

}

MakeDutchPage* MakeDutchPage::getInstance() {
    if (MakeDutchPage::instance == nullptr) {
        MakeDutchPage::instance = new MakeDutchPage();
    }

    return MakeDutchPage::instance;
}

MakeDutchPage::~MakeDutchPage() {
    delete instance;
}