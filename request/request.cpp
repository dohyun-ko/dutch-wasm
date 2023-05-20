#include "request.h"
#include <emscripten/fetch.h>
#include <emscripten.h>
#include <string>
#include <iostream>
using namespace std;  

Request::Request(string url, string method, string body) {
    this->url = url;
    this->method = method;
    this->body = body;
    this->onSuccess = NULL;
    this->onError = NULL;
    this->onProgress = NULL;
}

Request::~Request() {}

void Request::send() {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, this->method.c_str());
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    if (body != "") {
        attr.requestData = this->body.c_str();
        attr.requestDataSize = this->body.length();
    }
    if(this->onSuccess != NULL) {
        attr.onsuccess = this->onSuccess;
    }
    if(this->onError != NULL) {
        attr.onerror = this->onError;
    }
    if(this->onProgress != NULL){
        attr.onprogress = this->onProgress;
    }
    this->fetch = emscripten_fetch(&attr, this->url.c_str());
    while(this->fetch->readyState != 4){
        emscripten_sleep(100);
    }
    cout << "Request sent"  << fetch->data << endl;
    emscripten_fetch_close(this->fetch);
}

void Request::setOnSuccess(void (*onSuccess)(emscripten_fetch_t *fetch)) {
    this->onSuccess = onSuccess;
}

void Request::setOnError(void (*onError)(emscripten_fetch_t *fetch)) {
    this->onError = onError;
}

void Request::setOnProgress(void (*onProgress)(emscripten_fetch_t *fetch)) {
    this->onProgress = onProgress;
}