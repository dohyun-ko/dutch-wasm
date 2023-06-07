#include "sendDetailPage.h"

SendDetailPage* SendDetailPage::instance = nullptr;

SendDetailPage::SendDetailPage() : Element("div") {

}

SendDetailPage* SendDetailPage::getInstance() {
    if (SendDetailPage::instance == nullptr) {
        SendDetailPage::instance = new SendDetailPage();
    }

    return SendDetailPage::instance;
}

SendDetailPage::~SendDetailPage() {
    delete instance;
}