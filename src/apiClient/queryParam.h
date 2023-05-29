#pragma once
#include <string>
#include <vector>
using namespace std;

enum queryParamFormat { SINGLE, MULTIPLE };

class QueryParam {
    public:
        QueryParam(string key, string value);
        string getKey();
        string getValue();
        string getQueryForm(queryParamFormat format=SINGLE);
    private:
        string key;
        string value;
};

class QueryParamList {
    public:
        QueryParamList();
        QueryParamList(vector<QueryParam> queryParamList);
        void addQueryParam(QueryParam queryParam);
        string getQueryForm();
    private:
        vector<QueryParam> queryParamList;
};
