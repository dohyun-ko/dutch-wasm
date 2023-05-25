#include <emscripten/fetch.h>
#include <string>
#pragma once
using namespace std;

class ApiClient {
    public:
        ApiClient(string url, string method, string body="", int timeout=10000);
        ~ApiClient();
        emscripten_fetch_t* send();
        emscripten_fetch_t* getResponse();
    private:
        int timeout;
        string url;
        string method;
        string body;
        emscripten_fetch_t *response;
};