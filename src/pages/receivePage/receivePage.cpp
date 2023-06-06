#include "receivePage.h"

ReceivePage* ReceivePage::instance = nullptr;

ReceivePage::ReceivePage() : Element("div") {

}

ReceivePage* ReceivePage::getInstance() {
    if (ReceivePage::instance == nullptr) {
        ReceivePage::instance = new ReceivePage();
    }

    return ReceivePage::instance;
}

ReceivePage::~ReceivePage() {
    delete instance;
}
