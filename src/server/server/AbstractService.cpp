#include "AbstractService.h"
#include "ServiceException.h"
#include <iostream>

using namespace server;
using namespace std;

AbstractService::AbstractService(std::string pattern) {
    this->pattern = pattern;
}

AbstractService::~AbstractService() {
    //delete this->pattern;
}



HttpStatus AbstractService::get(Json::Value &out, int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::post(Json::Value &out, Json::Value &in) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::put(int id, Json::Value &in) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::remove (int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

const std::string & AbstractService::getPattern() const {
    return pattern;
}