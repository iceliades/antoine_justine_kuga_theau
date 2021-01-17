#include "AbstractService.h"
#include "ServiceException.h"
#include <iostream>

using namespace server;
using namespace std;

AbstractService::AbstractService(const std::string& pattern)
{
    this->pattern = pattern;
}

AbstractService::~AbstractService() {
    //delete this->pattern;
}



const HttpStatus AbstractService::get(Json::Value& out, int id)  {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::post (const Json::Value& in, int id,Json::Value& out) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::put (Json::Value& out, const  Json::Value& in){
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::remove (int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}