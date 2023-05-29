#include <string>
#include <vector>

#include "queryParam.h"

using namespace std;

QueryParam::QueryParam(string key, string value) {
    this->key = key;
    this->value = value;
}

string QueryParam::getKey() {
    return this->key;
}

string QueryParam::getValue() {
    return this->value;
}

string QueryParam::getQueryForm(queryParamFormat format) {
    return (format == SINGLE ? "?" : "&") + this->key + "=" + this->value;
}

QueryParamList::QueryParamList() {
    this->queryParamList = {};
}

QueryParamList::QueryParamList(vector<QueryParam> queryParamList) {
    this->queryParamList = queryParamList;
}

void QueryParamList::addQueryParam(QueryParam queryParam) {
    this->queryParamList.push_back(queryParam);
}

string QueryParamList::getQueryForm() {
    string queryForm = "";
    for (int i = 0; i < this->queryParamList.size(); i++) {
        queryForm += this->queryParamList[i].getQueryForm(i == 0 ? SINGLE : MULTIPLE);
    }
    return queryForm;
}
