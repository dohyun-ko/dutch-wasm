#include <emscripten/fetch.h>
#include <string>
#pragma once
using namespace std;

class Request {
    public:
        Request(string url, string method, string body="");
        ~Request();
        void send();
        void setOnSuccess(void (*onSuccess)(emscripten_fetch_t *fetch));
        void setOnError(void (*onError)(emscripten_fetch_t *fetch));
        emscripten_fetch_t* getFetch();
    private:
        string url;
        string method;
        string body;
        emscripten_fetch_t *fetch;
        void (*onSuccess)(emscripten_fetch_t *fetch);
        void (*onError)(emscripten_fetch_t *fetch);  
};