#include "apiClient.h"
#include "queryParam.h"
#include <emscripten/fetch.h>
#include <string>
#include <iostream>
using namespace std;  

//init the api client
ApiClient::ApiClient(string url, string method, vector<QueryParam> queryParams,string body, int timeout) {
    this->url = url;
    this->method = method;
    this->body = body;
    this->timeout = timeout;
    this->queryParams = QueryParamList(queryParams);
}

//close the api client and free the memory (delete response object)
ApiClient::~ApiClient() {
    cout << "ApiClient destructor called" << endl;
    emscripten_fetch_close(this->response);
}

//get the response from the server
void ApiClient::send() {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, this->method.c_str());
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_WAITABLE;
    attr.timeoutMSecs = this->timeout;
    string urlWithQueryParams = this->url + this->queryParams.getQueryForm();
    this->response = emscripten_fetch(&attr, urlWithQueryParams.c_str());
    while(this->response->numBytes != this->response->totalBytes || this->response->totalBytes == 0){
        cout << this->response->numBytes << " " << this->response->totalBytes << endl;
        emscripten_sleep(100);
    }
    cout<<"Response: "<<response->data<<endl;
}

//get the response already fetched
emscripten_fetch_t* ApiClient::getResponse() {
    return this->response;
}