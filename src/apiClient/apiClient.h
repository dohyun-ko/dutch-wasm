#include <emscripten/fetch.h>
#include <string>
#include <nlohmann/json.hpp>

#include "queryParam.h"
#pragma once
using namespace std;
using json = nlohmann::json;

class ApiClient {
    public:
        ApiClient(string url, string method, vector<QueryParam> queryParams={} ,string body="", int timeout=10000);
        ~ApiClient();
        void send();
        emscripten_fetch_t* getResponse();
        string getData();
        json getJsonData();
    private:
        int timeout;
        string url;
        string method;
        string body;
        QueryParamList queryParams;
        emscripten_fetch_t *response;
};