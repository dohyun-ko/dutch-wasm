#include "sendPage.h"

SendPage* SendPage::instance = nullptr;

SendPage::SendPage() : Element("div") {

}

SendPage* SendPage::getInstance() {
    if (SendPage::instance == nullptr) {
        SendPage::instance = new SendPage();
    }

    return SendPage::instance;
}

SendPage::~SendPage() {
    delete instance;
}