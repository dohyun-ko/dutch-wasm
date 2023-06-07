#include "receiveDetailPage.h"

ReceiveDetailPage* ReceiveDetailPage::instance = nullptr;

ReceiveDetailPage::ReceiveDetailPage() : Element("div") {

}

ReceiveDetailPage* ReceiveDetailPage::getInstance() {
    if (ReceiveDetailPage::instance == nullptr) {
        ReceiveDetailPage::instance = new ReceiveDetailPage();
    }

    return ReceiveDetailPage::instance;
}

ReceiveDetailPage::~ReceiveDetailPage() {
    delete instance;
}