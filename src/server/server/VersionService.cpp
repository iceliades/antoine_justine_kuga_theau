#include "VersionService.h"

using namespace std;
using namespace server;


VersionService::VersionService(){
    this->AbstractService("/version");
}

HttpStatus const VersionService::get(Json::Value& out, int in){
    out["version"] = "0.1";
    return HttpStatus::OK;
}