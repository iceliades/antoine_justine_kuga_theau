#include "AbstractService.h"
#include "ServiceException.h"
#include <iostream>

using namespace server;
using namespace std;

AbstractService::AbstractService(const std::string pattern) {
    this->pattern = pattern;
}

AbstractService::~AbstractService() {
    //delete this->pattern;
}



HttpStatus AbstractService::get(Json::Value &out, int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::post(Json::Value &out, const Json::Value &in) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::put (Json::Value& out, const  Json::Value& in){
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::remove (int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}