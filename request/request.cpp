#include "request.h"
#include <emscripten/fetch.h>
#include <string>
#include <iostream>
using namespace std;  

Request::Request(string url, string method, string body) {
    this->url = url;
    this->method = method;
    this->body = body;
}

Request::~Request() {
    emscripten_fetch_close(this->fetch);
}

void Request::send() {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, this->method.c_str());
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    if (body != "") {
        attr.requestData = this->body.c_str();
        attr.requestDataSize = this->body.length();
    }
    attr.onsuccess = this->onSuccess;
    attr.onerror = this->onError;
    this->fetch = emscripten_fetch(&attr, this->url.c_str());
}

void Request::setOnSuccess(void (*onSuccess)(emscripten_fetch_t *fetch)) {
    this->onSuccess = onSuccess;
}

void Request::setOnError(void (*onError)(emscripten_fetch_t *fetch)) {
    this->onError = onError;
}

emscripten_fetch_t* Request::getFetch() {
    return this->fetch;
}