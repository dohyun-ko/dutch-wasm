#include "apiClient.h"
#include <emscripten/fetch.h>
#include <emscripten.h>
#include <string>
#include <iostream>
using namespace std;  

ApiClient::ApiClient(string url, string method, string body, int timeout) {
    this->url = url;
    this->method = method;
    this->body = body;
    this->timeout = timeout;
}

ApiClient::~ApiClient() {
    emscripten_fetch_close(this->response);
}

//get the response from the server synchronously
emscripten_fetch_t* ApiClient::send() {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, this->method.c_str());
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.timeoutMSecs = this->timeout;

    this->response = emscripten_fetch(&attr, this->url.c_str());

    while(this->response->readyState != 4){
        emscripten_sleep(10);
    }
    return this->response;
}

emscripten_fetch_t* ApiClient::getResponse() {
    return this->response;
}