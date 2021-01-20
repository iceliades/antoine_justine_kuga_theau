#include "ServicesManager.h"
#include "ServiceException.h"
#include <iostream>

using namespace std;
using namespace server;




AbstractService * ServicesManager::findService(std::string &url) {
    for (auto &service : services){
        const string &pattern(service->getPattern());
        if (url.find(pattern) != 0 || (url.size() > pattern.size() && url[pattern.size()] != '/'))
            continue;
        return service.get();
    }
    return nullptr;
}

HttpStatus ServicesManager::queryService(std::string &out, std::string &in, std::string url, std::string method) {
    AbstractService *service = findService(url);

    if (!service) throw ServiceException(HttpStatus::NOT_FOUND, "Service " + url + " inconnu");

    const string &pattern(service->getPattern());
    int id = -1; // not found



    if (url.size() > pattern.size())
    {
        string end = url.substr(pattern.size());
        if (end[0] != '/' || end.substr(1).empty()) throw ServiceException(HttpStatus::BAD_REQUEST, "Mauvaise url (on veut : <servicename>/<id>)");
        end = end.substr(1);
        try
        {
            size_t pos = 0;
            id = stoi(end, &pos);
            if (pos != end.size())
                throw ServiceException(HttpStatus::BAD_REQUEST, "L'url : " + end + " a un id incorrect");
        }
        catch (...) {
            throw ServiceException(HttpStatus::BAD_REQUEST, "L'url : '" + end + " a un id incorrect");
            }
    }
    // HTTP Status -> test des enums

    if (method == "GET"){
        Json::Value jsonOut;
        HttpStatus status = service->get(jsonOut, id);
        out = jsonOut.toStyledString();
        return status;
    }
    else if (method == "PUT"){
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in, jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST, "Donnée erreur: " + jsonReader.getFormattedErrorMessages());
        return service->put(id ,jsonIn);
    }
    else if (method == "POST"){
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in, jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST, "Donnée erreur: " + jsonReader.getFormattedErrorMessages());
        Json::Value jsonOut;
        HttpStatus status = service->post(jsonOut, jsonIn);
        out = jsonOut.toStyledString();
        return status;
    }

    else if (method == "DELETE"){
        return service->remove(id);
    }
    throw ServiceException(HttpStatus::BAD_REQUEST, "Method " + method + " invalide");
}

void ServicesManager::registerService(std::unique_ptr<AbstractService> service) {
    services.push_back(std::move(service));
}
