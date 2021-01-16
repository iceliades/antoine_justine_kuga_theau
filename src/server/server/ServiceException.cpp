#include "ServiceException.h"

using namespace std;
using namespace server; 


ServiceException::ServiceException(HttpStatus status, std::string& message){
    switch(status){
        case OK :
        ; break;

        case CREATED :
        ; break;

        case NO_CONTENT :
        ; break;

        case BAD_REQUEST :
        ; break;

        case NOT_FOUND :
        ; break;

        case SERVER_ERROR :
        ; break;

        case NOT_IMPLEMENTED :
        ; break;

        case OUT_OF_RESSOURCES :
        ; break;
    }
}


